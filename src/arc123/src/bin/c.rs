#![allow(unused_macros, unused_imports)]

use proconio::marker::Bytes;
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
        t: usize,
    }

    for _ in 0..t {
        solve();
    }
}

fn solve() {
    proconio::input! { n: Bytes }

    let mut dp = vec![(10, 10); n.len()+1];
    dp[0] = (0, 0);
    for (i, &c) in n.iter().enumerate() {
        let a = c - b'0';

        for j in dp[i].0..6 {
            if j <= a && a <= 9.min(3*j) {
                dp[i+1].0 = dp[i+1].0.min(j);
            }
            if a > 0 {
                if j <= a-1 && a-1 <= 9.min(3*j) {
                    dp[i+1].1 = dp[i+1].1.min(j);
                }
            }
        }

        for j in dp[i].1..6 {
            if 10+a <= 3*j {
                dp[i+1].0 = dp[i+1].0.min(j);
            }
            if a > 0 {
                if 9+a <= 3*j {
                    dp[i+1].1 = dp[i+1].1.min(j);
                }
            }
        }

        if a == 0 {
            dp[i+1].0 = dp[i+1].0.min(dp[i].1.max(4));
            dp[i+1].1 = dp[i+1].1.min(dp[i].1.max(3));
        }
    }
    // dbg!(&dp);

    println!("{}", dp[n.len()].0)
}