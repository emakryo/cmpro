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
        mut xs: [(usize, usize, usize); n],
    }

    xs.sort_by_key(|x| (x.0+x.1, x.1));

    let m = 20001;
    let mut dp = vec![vec![0; m]; n+1];

    for i in 0..n {
        dp[i+1] = dp[i].clone();
        for w in 0..=xs[i].1 {
            if w+xs[i].0 < m {
                dp[i+1][w+xs[i].0] = dp[i+1][w+xs[i].0].max(dp[i][w] + xs[i].2);
            }
        }
    }

    println!("{}", dp[n].iter().max().unwrap());
}