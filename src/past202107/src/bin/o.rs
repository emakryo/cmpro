#![allow(unused_macros, unused_imports)]

use std::collections::BinaryHeap;
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
        xs: [(i64, i64); n],
    }

    let mut cummax = vec![0; n+1];
    let mut cumsum = vec![0; n+1];
    for i in 0..n {
        cummax[i+1] = cummax[i].max(xs[i].1);
        cumsum[i+1] = cumsum[i] + xs[i].0;
    }

    let mut dp = vec![0; n+1];
    let mut hp = BinaryHeap::new();
    hp.push((0, xs[0].0));

    for i in 0..n {
        if xs[i].1 <= cummax[i] {
            dp[i+1] = dp[i];
        } else {
            while let Some(&(_, y)) = hp.peek() {
                if y < xs[i].1 {
                    hp.pop();
                } else {
                    break;
                }
            }
            if hp.len() == 0 {
                println!("-1");
                return;
            }
            dp[i+1] = hp.peek().unwrap().0 - xs[i].1;
        }

        if i < n-1 {
            hp.push((dp[i+1], dp[i+1] + cumsum[i+2]));
        }
    }

    println!("{}", dp[n]+cumsum[n]);
}