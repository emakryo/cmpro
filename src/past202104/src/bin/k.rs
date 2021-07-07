#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

macro_rules! max {
    ($x:expr, $y:expr) => {
        $x = $x.max($y);
    };
}

fn main() {
    proconio::input!{
        n: usize,
        xs: [(i64, i64); n],
    }
    
    let mut dp = vec![vec![-1000000000000; 100]; n+1];
    dp[0][0] = 0;

    for i in 0..n {
        for j in 0..100 {
            max!(dp[i+1][j], dp[i][j]);
            max!(dp[i+1][(j+xs[i].0 as usize)%100], dp[i][j] + xs[i].1 - xs[i].0 + (j as i64 + xs[i].0) / 100 * 20);
        }
    }

    println!("{}", dp[n].iter().max().unwrap());
}