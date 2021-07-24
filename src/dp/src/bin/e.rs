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

macro_rules! chmin {
    ($x:expr, $y:expr) => {
        $x = $x.min($y);
    };
}

fn main() {
    proconio::input!{
        n: usize,
        w: i64,
        xs: [(i64, usize); n],
    }

    let inf = 1000000000000i64;
    let v = 100005;
    let mut dp = vec![vec![inf; v]; n+1];
    dp[0][0] = 0;

    for i in 0..n {
        for j in 0..v {
            chmin!(dp[i+1][j], dp[i][j]);
            if j+xs[i].1 < v {
                chmin!(dp[i+1][j+xs[i].1], dp[i][j]+xs[i].0);
            }
        }
    }

    let mut ans = 0;
    for i in 0..v {
        if dp[n][i] <= w {
            ans = i;
        }
    }
    println!("{}", ans);
}