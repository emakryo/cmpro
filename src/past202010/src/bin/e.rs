#![allow(unused_macros, unused_imports)]

use proconio::marker::Chars;
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
        n: usize,
        s: Chars,
    }

    use itertools::Itertools;

    for p in s.iter().permutations(n) {
        if p.iter().zip(&s).any(|(&&x,&y)| x!=y) && p.iter().rev().zip(&s).any(|(&&x, &y)| x!=y) {
            println!("{}", p.iter().join(""));
            return;
        }
    }

    println!("None");
}