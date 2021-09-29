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
        mut d: usize,
    }

    let mut ds = vec![0; 3];
    while d % 2 == 0 {
        ds[0] += 1;
        d /= 2;
    }
    while d % 3 == 0 {
        ds[1] += 1;
        d /= 3;
    }
    while d % 5 == 0 {
        ds[2] += 1;
        d /= 5;
    }
    if d > 1 {
        println!("0");
        return;
    }

    let m = 65;
    let mut dp = vec![vec![vec![0.0; 65]; 65]; 65];
    dp[0][0][0] = 1.0;

    for _ in 0..n {
        let mut next = vec![vec![vec![0.0; 65]; 65]; 65];
        for p in 0..m {
            for q in 0..m {
                for r in 0..m {
                    next[p][q][r] += dp[p][q][r];
                    next[(m-1).min(p+1)][q][r] += dp[p][q][r];
                    next[p][(m-1).min(q+1)][r] += dp[p][q][r];
                    next[(m-1).min(p+2)][q][r] += dp[p][q][r];
                    next[p][q][(m-1).min(r+1)] += dp[p][q][r];
                    next[(m-1).min(p+1)][(m-1).min(q+1)][r] += dp[p][q][r];
                }
            }
        }

        dp = next;
    }

    let mut sum = 0.0;
    for p in 0..m {
        for q in 0..m {
            for r in 0..m {
                if p >= ds[0] && q >= ds[1] && r >= ds[2] {
                    sum += dp[p][q][r];
                }
            }
        }
    }

    println!("{}", sum / 6.0f64.powi(n as i32));
}