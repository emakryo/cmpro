#![allow(unused_macros, unused_imports)]

use proconio::marker::{Bytes, Chars};
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
        n: Bytes,
    }

    let mut dp = vec![[0, 0]; n.len()+1];
    let mut ones = 0usize;
    let mut f = true;
    let mut k = 0;
    for (i, &c) in n.iter().enumerate() {
        let c = (c - b'0') as usize;

        k = 10 * k + c;
        ones = 10 * ones + 1;

        if f && c == 1 {
            dp[i+1][0] = dp[i][0] + 1;
        } else {
            f = false;
            dp[i+1][0] = dp[i][0];
        }

        dp[i+1][1] = dp[i][1] * 10 + dp[i][0] * c;

        dbg!(k, ones);

        if ones < k {
            dp[i+1][1] += i+1;
        } else {
            dp[i+1][1] += i;
        }
    }

    dbg!(&dp);

    println!("{}", dp[n.len()][0] + dp[n.len()][1]);
}