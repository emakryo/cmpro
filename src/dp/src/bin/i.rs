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
        p: [f64; n],
    }

    let mut dp = vec![vec![0.0; 2*n+1]; n+1];
    let offset = n;

    dp[0][offset] = 1.0;

    for i in 0..n {
        for j in 0..2*n+1 {
            if j+1 < 2*n+1 {
                dp[i+1][j+1] += dp[i][j] * p[i];
            }
            if j > 1 {
                dp[i+1][j-1] += dp[i][j] * (1.0-p[i]);
            }
        }
    }

    println!("{}", dp[n][offset..].iter().sum::<f64>());
}