#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

use std::vec;

use itertools::Itertools;
use proconio::marker::Chars;

fn main() {
    proconio::input!{
        s: Chars,
        k: usize,
    }

    let mut xs = vec![];
    for p in s.iter().permutations(s.len()) {
        let x = p.into_iter().collect::<String>();
        xs.push(x);
    }
    xs.sort();
    xs.dedup();
    println!("{}", xs[k-1]);
}