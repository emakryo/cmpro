#![allow(unused_macros, unused_imports)]

use std::collections::HashMap;
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

use proconio::marker::Bytes;

fn main() {
    proconio::input!{
        n: Bytes,
        k: usize,
    }

    let mut dp = HashMap::new();
    let mut prod = 1;
    for i in 0..n.len() {
        let d = (n[i]-b'0') as usize;
        let mut next = HashMap::new();
        for (&p, &v) in &dp {
            for d in 0..=9 {
                *next.entry(p*d).or_insert(0usize) += v;
            }
        }
        let s = if i == 0 { 1 } else { 0 };
        for j in s..d {
            *next.entry(prod*j).or_insert(0) += 1;
        }

        if i > 0 {
            for j in 1..=9 {
                *next.entry(j).or_insert(0) += 1;
            }
        }
        // dbg!(i, n/d);

        prod *= d;
        dp = next;
    }

    let mut ans = 0;
    for (a, v) in dp {
        if a <= k {
            ans += v;
        }
    }

    if prod <= k {
        ans += 1;
    }

    println!("{}", ans);
}