#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        a: [usize; n],
    }
    let sum: usize = a.iter().sum();

    let inf = 1e100f64;
    let mut dp = vec![vec![vec![inf; sum+1]; sum+1]; n];
    let dist: Vec<_> = (0..101).map(|x| (x as f64).hypot(1.0)).collect();
    dp[0][0][0] = 0.0;
    for i in 0..n-1 {
        for j in 0..=sum {
            for k in 0..=sum {
                if dp[i][j][k] == inf { continue }
                for l in 0..=sum {
                    if j + l > sum { break }
                    let d = if l > k { l - k } else { k - l };
                    dp[i+1][j+l][l] = dp[i+1][j+l][l].min(dp[i][j][k] + dist[d]);
                }
            }
        }
    }

    println!("{}", dp[n-1][sum][0]);
}