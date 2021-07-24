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
        xs: [(i64, i64, i64); n],
    }

    let inf = 1000000000000i64;
    let mut dp = vec![(inf, inf, inf); n+1];
    dp[0] = (0, 0, 0);
    for i in 0..n {
        dp[i+1].0 = xs[i].0 + dp[i].1.max(dp[i].2);
        dp[i+1].1 = xs[i].1 + dp[i].0.max(dp[i].2);
        dp[i+1].2 = xs[i].2 + dp[i].1.max(dp[i].0);
    }

    println!("{}", dp[n].0.max(dp[n].1).max(dp[n].2));
}