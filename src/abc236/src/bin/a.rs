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
        mut s: Chars,
        a: usize,
        b: usize,
    }

    s.swap(a-1, b-1);

    println!("{}", s.iter().collect::<String>());
}