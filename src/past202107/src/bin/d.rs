#![allow(unused_macros)]

macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        mut s: proconio::marker::Bytes,
    }

    let mut i = 0;
    while i+2 < n {
        let t = s[i..i+3].to_owned();
        match t.as_slice() {
            b"axa" | b"ixi" | b"uxu" | b"exe" | b"oxo" => {
                s[i] = b'.';
                s[i+1] = b'.';
                s[i+2] = b'.';
                i += 3;
            },
            _ => {
                i += 1;
            }
        }
    }

    println!("{}", String::from_utf8(s).unwrap());
}