#![allow(unused_macros, unused_imports)]

use std::collections::{BinaryHeap, HashMap};
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
        m: usize,
        a: [i64; n],
        xs: [(usize, usize, i64); m],
    }

    let mut dp = vec![0; n+1];
    let mut ls = vec![vec![]; n+1];
    for (l, r, c) in xs {
        ls[l].push((r, c));
    }

    let mut rs = BinaryHeap::new();

    for i in 0..n {
        for &(r, c) in &ls[i+1] {
            rs.push((dp[i]-c, r));
        }
        dp[i+1] = dp[i] - a[i];
        while let Some(&(x, r)) =rs.peek() {
            if i+1 <= r {
                dp[i+1] = dp[i+1].max(x);
                break;
            } else {
                rs.pop();
            }
        }
        dbg!(i+1, dp[i+1]);
    }

    println!("{}", dp[n] + a.iter().sum::<i64>());
}