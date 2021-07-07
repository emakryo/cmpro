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
        h: usize,
        w: usize,
        a: [[i64; w]; h],
    }

    let mut dp = vec![vec![vec![std::i64::MIN; h+w]; w]; h];

    for x in 0..h {
        for y in 0..w {
            dp[x][y][1] = a[x][y];
            for k in 1..h+w {
                if x >= 1 {
                    max!(dp[x][y][k], dp[x-1][y][k-1]+a[x][y]);
                    max!(dp[x][y][k], dp[x-1][y][k]);
                }
                if y >= 1 {
                    max!(dp[x][y][k], dp[x][y-1][k-1]+a[x][y]);
                    max!(dp[x][y][k], dp[x][y-1][k]);
                }
            }
        }
    }

    for i in 1..h+w {
        println!("{}", dp[h-1][w-1][i]);
    }
}