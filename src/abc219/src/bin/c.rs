#![allow(unused_macros, unused_imports)]

use proconio::marker::{Bytes, Chars};
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

fn main() {
    proconio::input!{
        x: Bytes,
        n: usize,
        s: [Bytes; n],
    }

    let mut zs = vec![];
    let mut map = vec![Default::default(); 26];

    for (i, c) in x.iter().enumerate() {
        let c = (*c - b'a') as usize;
        map[c] = (i as u8 + b'a') as char;
    }
    for si in &s {
        let z = si.iter().map(|c| map[(c-b'a') as usize]).collect::<String>();
        zs.push(z);
    }

    let mut idx = (0..n).collect::<Vec<usize>>();

    idx.sort_by_key(|i| &zs[*i]);

    for i in 0..n {
        println!("{}", s[idx[i]].iter().map(|&x| x as char).collect::<String>());
    }
}