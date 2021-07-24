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
        a: [usize; n],
    }

    let mut cnt = vec![0; 4];
    for i in 0..n {
        cnt[a[i]] += 1;
    }

    let mut dp = vec![vec![vec![0.0; n+1]; n+1]; n+1];

    for i in 0..=n {
        for j in 0..=n {
            for k in 0..=n {
                if i+j+k > n || (i==0 && j==0 && k==0) { continue }
                dp[i][j][k] = n as f64 / (i+j+k) as f64;

                if k > 0 {
                    dp[i][j][k] += dp[i][j][k-1] * (k as f64) / (i+j+k) as f64;
                }

                if j > 0 && k < n {
                    dp[i][j][k] += dp[i][j-1][k+1] * (j as f64) / (i+j+k) as f64;
                }

                if i > 0 && j < n {
                    dp[i][j][k] += dp[i-1][j+1][k] * (i as f64) / (i+j+k) as f64;
                }

                dbg!(i, j, k, dp[i][j][k]);
            }
        }
    }

    println!("{}", dp[cnt[3]][cnt[2]][cnt[1]]);
}