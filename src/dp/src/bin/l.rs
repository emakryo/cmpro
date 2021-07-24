#![allow(unused_macros, unused_imports)]
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
        a: [i64; n],
    }

    let mut dp = vec![vec![0; n+1]; n+1];

    for w in 1..=n {
        for i in 0..n {
            if i+w > n { break }
            if w%2 == n%2 {
                dp[i][i+w] = (dp[i][i+w-1] + a[i+w-1]).max(dp[i+1][i+w] + a[i]);
            } else {
                dp[i][i+w] = (dp[i][i+w-1] - a[i+w-1]).min(dp[i+1][i+w] - a[i]);
            }
        }
    }

    println!("{}", dp[0][n]);
}