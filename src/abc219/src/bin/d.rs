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
        x: usize,
        y: usize,
        xs: [(usize, usize); n],
    }

    let inf = 100000;
    let mut dp = vec![vec![inf; y+1]; x+1];
    dp[0][0] = 0;

    for (a, b) in xs {
        let mut next = dp.clone();
        for p in 0..=x {
            for q in 0..=y {
                let np = x.min(p+a);
                let nq = y.min(q+b);
                next[np][nq] = next[np][nq].min(dp[p][q]+1);
                // eprintln!("{} {} {} {} {} {} {} {}", a, b, p, q, np, nq, dp[p][q], next[np][nq]);
            }
        }
        dp = next;
    }

    if dp[x][y] < inf {
        println!("{}", dp[x][y]);
    } else {
        println!("{}", -1);
    }
}