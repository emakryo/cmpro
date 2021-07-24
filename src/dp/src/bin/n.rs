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

    let inf = 100000000000000i64;
    let mut dp = vec![vec![inf; n+1]; n+1];
    let mut cm = vec![0; n+1];
    for i in 0..n {
        cm[i+1] = cm[i] + a[i];
    }

    for w in 1..=n {
        for i in 0..=n-w {
            if w==1 {
                dp[i][i+1] = 0;
            } else {
                for j in i+1..i+w {
                    dbg!(i, j, i+w, dp[i][j] + dp[j][i+w] - cm[i] + cm[i+w]);
                    dp[i][i+w] = dp[i][i+w].min(dp[i][j] + dp[j][i+w] - cm[i] + cm[i+w]);
                }
                dbg!(i, w, dp[i][i+w]);
            }
        }
    }

    println!("{}", dp[0][n]);
}