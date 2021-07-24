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
    let n = 18;
    let m = 6;

    proconio::input!{
        s: [Chars; n],
    }

    let mut dp = vec![vec![0u64; 1<<(2*m)]; n+1];
    dp[0][0] = 1;
    for i in 0..n {
        let mut v = 0;
        let mut u = 0;
        for k in 0..m {
            if s[i][k] == '1' {
                v += 1<<k;
            }
            if s[i][k] == '?' {
                u += 1<<k;
            }
        }
        for s in 0..1<<(2*m) {
            if dp[i][s] > 0 {
                // dbg!(i, s, dp[i][s]);
            }
            for t in 0..1<<m {
                if (t^v) & (u^((1<<m)-1)) > 0 { continue; }
                let mut ok = true;
                for k in 0..m {
                    let mut x = (t>>k&1) + (s>>k&1) + (s>>(k+m)&1);
                    if k > 0 {
                        x += s>>(k-1)&1;
                    }
                    if k < m-1 {
                        x += s>>(k+1)&1;
                    }
                    if (s>>k&1) == 1 && x <= 2 || (s>>k&1) == 0 && x > 2 {
                        ok = false;
                    }
                }
                if dp[i][s] > 0 {
                    // dbg!(t);
                }

                if i == 0 || ok {
                    dp[i+1][(s<<m)&((1<<(2*m))-1)|t] += dp[i][s];
                }
            }
        }
    }

    let mut ans = 0;
    for s in 0..1<<(2*m) {
        let mut ok = true;
        for k in 0..m {
            let mut x = (s>>k&1) + (s>>(k+m)&1);
            if k > 0 {
                x += s>>(k-1)&1;
            }
            if k < m-1 {
                x += s>>(k+1)&1;
            }
            if (s>>k&1) == 1 && x <= 2 || (s>>k&1) == 0 && x > 2 {
                ok = false;
            }
        }
        if ok {
            ans += dp[n][s];
        }
    }

    println!("{}", ans);
}