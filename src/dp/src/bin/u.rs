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
        a: [[i64; n]; n],
    }

    let mut dp = vec![std::i64::MIN/2; 1<<n];
    let mut sum = vec![0; 1<<n];
    for s in 0..1<<n {
        for i in 0..n {
            for j in i+1..n {
                if (s>>i&1) == 1 && (s>>j&1) == 1 { sum[s] += a[i][j]; }
            }
        }
    }
    dp[0] = 0;
    for s in 1usize..1<<n {
        let mut t = s;
        loop {
            dp[s] = dp[s].max(dp[s^t] + sum[t]);
            if t == 0 { break }
            t = s & (t-1);
        }
        // dbg!(s, dp[s]);
    }

    println!("{}", dp[(1<<n)-1]);
}