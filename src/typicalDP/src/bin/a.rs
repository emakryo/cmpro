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
        p: [usize; n],
    }

    let mut dp = vec![false; 10001];
    dp[0] = true;
    for pi in p {
        for i in (0..10001).rev() {
            if dp[i] && i+pi < 10001 {
                dp[i+pi] = true;
            }
        }
    }

    let ans = dp.iter().filter(|x| **x).count();
    println!("{}", ans);
}