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
        x: [usize; n],
    }

    let x = x.iter().map(|i| 1usize<<i).sum::<usize>();

    let mut dp = vec![1e10f64; 1<<16];
    dp[0] = 0.0;
    for i in 1..=x {
        for k in 0..16 {
            let mut p = 1.0;
            let mut q = 0;
            if i>>k&1 > 0 {
                p += dp[i^(1<<k)] / 3.0;
            } else {
                q += 1;
            }
            if k > 0 && i>>(k-1)&1 > 0 {
                p += dp[i^(1<<(k-1))] / 3.0;
            } else {
                q += 1;
            }
            if k < 15 && i>>(k+1)&1 > 0 {
                p += dp[i^(1<<(k+1))] / 3.0;
            } else {
                q += 1;
            }
            if q < 3 {
                dp[i] = dp[i].min(p * 3.0 / (3.0 - q as f64));
                dbg!(i, k, dp[i]);
            }
        }
    }

    println!("{}", dp[x]);
}