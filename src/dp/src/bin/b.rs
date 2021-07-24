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
        k: usize,
        h: [i64; n],
    }

    let mut dp = vec![1000000000000i64; n];
    dp[0] = 0;
    for i in 0..n {
        for j in 1..=k {
            if i+j >= n { break }
            dp[i+j] = dp[i+j].min(dp[i]+(h[i]-h[i+j]).abs());
        }
    }

    println!("{}", dp[n-1]);
}