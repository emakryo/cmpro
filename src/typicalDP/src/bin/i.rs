#![allow(unused_macros, unused_imports)]

use proconio::marker::Chars;
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
        s: Chars,
    }

    let n = s.len();
    let mut dp = vec![vec![0; n+1]; n+1];

    for w in 3..=n {
        for i in 0..=n-w {
            let j = i + w;
            for k in i+1..j {
                dp[i][j] = dp[i][j].max(dp[i][k]+dp[k][j]);
            }
            if s[i] == 'i' && s[i+1] == 'w' && s[j-1] == 'i' && 3 * dp[i+2][j-1] == j - i - 3 {
                dp[i][j] = dp[i][j].max(dp[i+2][j-1] + 1);
            }
            if s[i] == 'i' && s[j-2] == 'w' && s[j-1] == 'i' && 3 * dp[i+1][j-2] == j - i - 3 {
                dp[i][j] = dp[i][j].max(dp[i+1][j-2] + 1);
            }
        }
    }

    println!("{}", dp[0][n]);
}