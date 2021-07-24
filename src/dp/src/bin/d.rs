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

macro_rules! chmax {
    ($x:expr, $y:expr) => {
        $x = $x.max($y);
    };
}

fn main() {
    proconio::input!{
        n: usize,
        w: usize,
        xs: [(usize, i64); n],
    }

    let inf = 1000000000000i64;
    let mut dp = vec![vec![-inf; w+1]; n+1];
    dp[0][0] = 0;
    for i in 0..n {
        for j in 0..w {
            chmax!(dp[i+1][j], dp[i][j]);
            if j+xs[i].0 <= w {
                chmax!(dp[i+1][j+xs[i].0], dp[i][j] + xs[i].1);
            }
        }
    }

    println!("{}", dp[n].iter().max().unwrap());
}