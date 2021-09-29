#![allow(unused_macros, unused_imports)]

use proconio::marker::Bytes;
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
        s: Bytes,
        k: usize,
    }

    let n = s.len();
    let mut next= vec![[n+1; 26]; n+1];

    for i in (0..n).rev() {
        next[i] = next[i+1];
        next[i][(s[i]-b'a') as usize] = i+1;
    }

    let mut dp = vec![0usize; n+1];

    let inf = 1000_000_000_000_000_000usize;
    for i in (0..=n).rev() {
        dp[i] = 1;
        for j in 0..26 {
            if next[i][j] <= n {
                dp[i] += dp[next[i][j]];
                if dp[i] > inf {
                    dp[i] = inf+1;
                }
            }
        }
    }
    dbg!(&dp);

    let mut ans = vec![];
    let mut k = k + 1;  // add empty string
    if dp[0] < k {
        println!("Eel");
        return;
    }

    let mut i = 0;
    while k > 0 {
        assert!(k <= dp[i]);
        if i > 0 {
            ans.push(s[i-1]);
        }
        k -= 1;
        let mut ni = 0;
        for j in 0..26 {
            if next[i][j] > n {
                continue;
            }
            ni = next[i][j];
            if k > dp[next[i][j]] {
                k -= dp[next[i][j]];
            } else {
                break;
            }
        }
        i = ni;
    }

    println!("{}", String::from_utf8(ans).unwrap());
}