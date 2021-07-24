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
        k: usize,
        a: [usize; n],
    }

    let mut dp = vec![false; k+1];

    for x in 0..k+1 {
        let mut win = false;
        for i in 0..n {
            if x >= a[i] {
                if !dp[x-a[i]] {
                    win = true;
                }
            }
        }
        dp[x] = win;
    }

    if dp[k] {
        println!("First");
    } else {
        println!("Second");
    }
}