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
        m: usize,
        mut a: [i64; n],
        mut b: [i64; m],
    }

    let mut dp = vec![vec![0; m+1]; n+1];
    a.reverse();
    b.reverse();

    let total = a.iter().chain(b.iter()).sum::<i64>();

    for i in 0..=n {
        for j in 0..=m {
            if i > 0 && j > 0 {
                dp[i][j] = (-dp[i-1][j] + a[i-1]).max(-dp[i][j-1] + b[j-1]);
            } else if i > 0 {
                dp[i][j] = -dp[i-1][j] + a[i-1];
            } else if j > 0 {
                dp[i][j] = -dp[i][j-1] + b[j-1];
            }
        }
    }
    dbg!(&dp);

    println!("{}", (total + dp[n][m])/2);
}