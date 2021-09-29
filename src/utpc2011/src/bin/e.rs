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
        mut xs: [(usize, usize); n],
    }

    xs.sort_by_key(|x| x.1);
    let mut dp = vec![usize::max_value()/2; n+1];
    dp[0] = 0;

    let mut ans = 0;
    for (a, b) in xs {
        for i in (0..n).rev() {
            if dp[i]+a <= b {
                dp[i+1] = dp[i+1].min(dp[i]+a);
                ans = ans.max(i+1);
            }
        }
    }

    println!("{}", ans);
}