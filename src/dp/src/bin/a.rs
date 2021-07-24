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
        h: [i64; n],
    }

    let mut dp = vec![1000000000000i64; n];
    dp[0] = 0;
    for i in 0..n-1 {
        if i+1 < n {
            dp[i+1] = dp[i+1].min(dp[i]+(h[i]-h[i+1]).abs());
        }
        if i+2 < n {
            dp[i+2] = dp[i+2].min(dp[i]+(h[i]-h[i+2]).abs());
        }
    }

    println!("{}", dp[n-1]);
}