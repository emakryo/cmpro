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

    let idx = s.iter().enumerate().find(|&(_, &c)| c == 'i').unwrap().0;
    let a = s[..idx].to_owned();
    let mut b = s[idx+3..].to_owned();
    b.reverse();

    let mut dp = vec![vec![0; b.len()+1]; a.len()+1];
    for (i, x) in a.iter().enumerate() {
        for (j, y) in b.iter().enumerate() {
            match (x, y) {
                ('(', ')') | (')', '(') | ('{', '}') | ('}', '{') | ('[', ']') | (']', '[') => {
                    dp[i+1][j+1] = (dp[i][j]+1).max(dp[i][j+1]).max(dp[i+1][j]);
                },
                _ => {
                    dp[i+1][j+1] = dp[i][j+1].max(dp[i+1][j]);
                }
            }
        }
    }

    println!("{}", 3+2*dp[a.len()][b.len()]);

}