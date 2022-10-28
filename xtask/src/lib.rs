use anyhow::{anyhow, Result};
use itertools::Itertools;
use quote::ToTokens;
use std::{
    io::Write,
    process::{Command, Stdio},
};
use syn::{
    parse_file, parse_quote, Attribute, File, ImplItem, ImplItemMethod, Item, ItemEnum, ItemFn,
    ItemImpl, ItemMod, ItemStruct, ItemTrait, Path, TraitItem, TraitItemMethod,
};

pub fn compress(input: &str, format: bool) -> Result<String> {
    let file = parse_file(input)?;
    let file = remove_tests(file);
    let file = remove_docs(file);
    let ret = file.into_token_stream().to_string();

    let ret = if format {
        rustfmt(&ret)?
    } else {
        remove_spaces(&ret)
    };

    Ok(ret)
}

fn remove_tests(mut file: File) -> File {
    fn item(input: Item) -> Option<Item> {
        match input {
            Item::Mod(i) => item_mod(i).map(Item::Mod),
            other => Some(other),
        }
    }

    fn item_mod(mut input: ItemMod) -> Option<ItemMod> {
        if input
            .attrs
            .iter()
            .filter(|&attr| {
                let test_attr: Attribute = parse_quote!(#[cfg(test)]);
                test_attr == *attr
            })
            .count()
            > 0
        {
            return None;
        }

        input.content = input
            .content
            .map(|(br, items)| (br, items.into_iter().filter_map(item).collect()));
        Some(input)
    }

    file.items = file.items.into_iter().filter_map(item).collect();
    file
}

fn remove_docs(file: File) -> File {
    fn attr(input: Attribute) -> Option<Attribute> {
        let doc: Path = parse_quote!(doc);
        if input.path == doc {
            None
        } else {
            Some(input)
        }
    }

    fn item(input: Item) -> Item {
        match input {
            Item::Enum(i) => Item::Enum(item_enum(i)),
            Item::Fn(i) => Item::Fn(item_fn(i)),
            Item::Impl(i) => Item::Impl(item_impl(i)),
            Item::Mod(i) => Item::Mod(item_mod(i)),
            Item::Struct(i) => Item::Struct(item_struct(i)),
            Item::Trait(i) => Item::Trait(item_trait(i)),
            other => other,
        }
    }

    fn item_enum(mut input: ItemEnum) -> ItemEnum {
        input.attrs = input.attrs.into_iter().filter_map(attr).collect();
        input
    }

    fn item_fn(mut input: ItemFn) -> ItemFn {
        input.attrs = input.attrs.into_iter().filter_map(attr).collect();
        input
    }

    fn item_impl(mut input: ItemImpl) -> ItemImpl {
        input.attrs = input.attrs.into_iter().filter_map(attr).collect();
        input.items = input.items.into_iter().map(impl_item).collect();
        input
    }

    fn impl_item(input: ImplItem) -> ImplItem {
        match input {
            ImplItem::Method(i) => ImplItem::Method(impl_item_method(i)),
            other => other,
        }
    }

    fn impl_item_method(mut input: ImplItemMethod) -> ImplItemMethod {
        input.attrs = input.attrs.into_iter().filter_map(attr).collect();
        input
    }

    fn item_mod(mut input: ItemMod) -> ItemMod {
        input.attrs = input.attrs.into_iter().filter_map(attr).collect();
        input.content = input
            .content
            .map(|(br, items)| (br, items.into_iter().map(item).collect()));
        input
    }

    fn item_struct(mut input: ItemStruct) -> ItemStruct {
        input.attrs = input.attrs.into_iter().filter_map(attr).collect();
        input
    }

    fn item_trait(mut input: ItemTrait) -> ItemTrait {
        input.attrs = input.attrs.into_iter().filter_map(attr).collect();
        input.items = input.items.into_iter().map(trait_item).collect();
        input
    }

    fn trait_item(input: TraitItem) -> TraitItem {
        match input {
            TraitItem::Method(i) => TraitItem::Method(trait_item_method(i)),
            other => other,
        }
    }

    fn trait_item_method(mut input: TraitItemMethod) -> TraitItemMethod {
        input.attrs = input.attrs.into_iter().filter_map(attr).collect();
        input
    }

    File {
        shebang: file.shebang,
        attrs: file.attrs,
        items: file.items.into_iter().map(item).collect(),
    }
}

fn rustfmt(src: &str) -> Result<String> {
    let mut rustfmt = Command::new("rustfmt")
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()?;

    {
        let mut stdin = rustfmt
            .stdin
            .take()
            .ok_or_else(|| anyhow!("Failed to pipe stdin to rustfmt"))?;
        stdin.write_all(src.as_bytes())?;
    }
    let output = rustfmt.wait_with_output()?;
    let out = std::str::from_utf8(&output.stdout)?.to_owned();

    Ok(out)
}

fn remove_spaces(src: &str) -> String {
    let mut ret = String::new();
    ret.push(src.chars().next().unwrap());
    fn need_space(pre: char, post: char) -> bool {
        fn is_token(c: char) -> bool {
            c.is_alphanumeric() || c == '_'
        }
        (is_token(pre) && is_token(post))
            || ((pre == '<' || pre == '>') && post == '-')
            || (pre == ':' && post == ':')
    }
    for (pre, c, post) in src.chars().tuple_windows() {
        if c == ' ' {
            if need_space(pre, post) {
                ret.push(c);
            }
        } else {
            ret.push(c)
        }
    }
    ret.push(src.chars().last().unwrap());
    ret
}
