#![allow(unused_macros, unused_imports)]

use std::collections::{HashMap, HashSet};
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 { a }
    else { gcd( b, a%b) }
}

fn main() {
    proconio::input!{
        n: usize,
        p: [(i64, i64); n],
    }

    let mut m = HashSet::<(i64, i64)>::new();
    for i in 0..n {
        for j in 0..n {
            if i == j { continue; }
            let a = p[i].0 - p[j].0;
            let b = p[i].1 - p[j].1;
            let g = gcd(a.abs(), b.abs());
            m.insert((a/g, b/g));
        }
    }

    println!("{}", m.len());
}