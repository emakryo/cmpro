#![allow(unused_macros, unused_imports)]

use std::collections::HashSet;
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
        l: usize,
        x: [usize; n],
        t: [usize; 3],
    }

    let inf = 1000000000;
    let x = x.into_iter().collect::<HashSet<_>>();
    let mut dp = vec![inf; l+1];
    dp[0] = 0;

    for i in 1..=l {
        dp[i] = dp[i-1] + t[0];
        if i >= 2 {
            dp[i] = dp[i].min(dp[i-2] + t[0] + t[1]);
        }
        if i >= 4 {
            dp[i] = dp[i].min(dp[i-4] + t[0] + 3 * t[1]);
        }
        if x.contains(&i) {
            dp[i] += t[2];
        }
    }
    dbg!(&dp);

    println!("{}", dp[l]
        .min(dp[l-1] + t[0] / 2 + t[1] / 2)
        .min(dp[l-2] + t[0] / 2 + 3 * t[1] / 2)
        .min(if l >= 3 { dp[l-3] + t[0] / 2 + 5 * t[1] / 2 } else { inf }) 
    );
}