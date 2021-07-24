#![allow(unused_macros, unused_imports)]

use std::collections::VecDeque;
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
        c: i64,
        h: [i64; n],
    }

    let inf = std::i64::MAX;
    let mut dp = vec![inf; n+1];
    let cf = vec![(-2*h[0], h[0]*h[0])];
    let mut cf = VecDeque::from(cf);
    dp[0] = 0;
    for i in 1..n {
        while cf.len() >= 2 && -(cf[0].1 - cf[1].1) <= h[i] * (cf[0].0 - cf[1].0) {
            cf.pop_front();
        }
        dp[i] = cf[0].0 * h[i] + cf[0].1 + h[i]*h[i] + c;

        let a = -2 * h[i];
        let b = h[i]*h[i]+dp[i];
        while cf.len() >= 2 {
            let m = cf.len()-1;
            let (a1, b1) = cf[m];
            let (a0, b0) = cf[m-1];
            if (a0-a1) * (b0-b) >= (a0-a) * (b0-b1) {
                cf.pop_back();
            } else {
                break;
            }
        }
        cf.push_back((a, b));
        // dbg!(&cf);
    }

    println!("{}", dp[n-1]);
}