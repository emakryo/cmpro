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
        h: usize,
        w: usize,
        c: [Chars; h],
    }

    let mut ans = 0;
    for i in 0..w-1 {
        let mut cost = vec![vec![0; h+1]; h+1];
        for j in 1..=h {
            for k in 1..=h {
                cost[j][k] = cost[j-1][k-1];
                if c[j-1][i] == c[k-1][i+1] {
                    cost[j][k] += 1;
                }
            }
        }

        let mut dp = vec![vec![0; h+1]; h+1];

        for j in 1..=h {
            for k in 1..=h {
                dbg!(j, k);
                dp[j][k] = cost[j][k] + dp[j-1][k].min(dp[j][k-1]);
            }
        }
        ans += dbg!(dp[h][h]);
    }

    println!("{}", ans);
}