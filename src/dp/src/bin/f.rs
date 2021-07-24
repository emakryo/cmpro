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
        t: Chars,
    }

    let mut dp = vec![vec![0; t.len()+1]; s.len()+1];

    for i in 0..s.len() {
        for j in 0..t.len() {
            if s[i] == t[j] {
                dp[i+1][j+1] = *[dp[i][j+1], dp[i+1][j], dp[i][j]+1].iter().max().unwrap();
            } else{
                dp[i+1][j+1] = dp[i+1][j].max(dp[i][j+1]);
            }
        }
    }

    let mut p = (s.len(), t.len());
    let mut ans = String::new();

    while dp[p.0][p.1] > 0 {
        let i = p.0-1;
        let j = p.1-1;
        if s[i]==t[j] && dp[p.0-1][p.1-1] + 1 == dp[p.0][p.1] {
            ans.push(s[i]);
            p.0 -= 1;
            p.1 -= 1;
        } else if dp[p.0-1][p.1] == dp[p.0][p.1] {
            p.0 -= 1;
        } else if dp[p.0][p.1-1] == dp[p.0][p.1] {
            p.1 -= 1;
        }
    }

    println!("{}", ans.chars().rev().collect::<String>());
}