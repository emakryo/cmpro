#![allow(unused_macros, unused_imports)]

use std::collections::BTreeMap;
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
        a: [usize; n],
    }

    let mut count = BTreeMap::<usize, usize>::new();

    for ai in a {
        *count.entry(ai).or_default() += 1;
    }

    let c = count.values().cloned().collect::<Vec<_>>();

    let mut dp = vec![[0; 4]; c.len()+1];
    dp[0][0] = 1;

    for (i, &ci) in c.iter().enumerate() {
        dp[i+1][0] = dp[i][0];
        dp[i+1][1] = dp[i][1] + ci;
        dp[i+1][2] = dp[i][2] + dp[i][1] * ci;
        dp[i+1][3] = dp[i][3] + dp[i][2] * ci;
    }

    println!("{}", dp[c.len()][3]);
}
