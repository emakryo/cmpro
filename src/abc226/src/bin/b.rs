#![allow(unused_macros, unused_imports)]

use std::{collections::HashSet, iter::FromIterator};
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
        mut l: [[i64]; n],
    }

    let m = HashSet::<Vec<i64>>::from_iter(l.into_iter());
    println!("{}", m.len());
}