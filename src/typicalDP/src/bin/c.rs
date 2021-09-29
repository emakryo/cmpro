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
        k: usize,
        r: [f64; 1<<k],
    }

    let mut dp = vec![vec![1.0; 1<<k]; k+1];

    for i in 0..k {
        for j in 0..1<<k {
            dp[i+1][j] = 0.0;
            let w = 1 << (i+1);
            let a = j % w;
            let b = j / w;
            let (s, t) = if a < 1<<i {
                (b*w+(1<<i), b*w+(1<<(i+1)))
            } else {
                (b*w, b*w+(1<<i))
            };  
            dbg!(i, j, s, t);
 
            for l in s..t {
                dp[i+1][j] += dp[i][j] * dp[i][l] / (1.0 + 10.0f64.powf((r[l]-r[j])/400.0));
            }
        }
    }

    for i in 0..1<<k {
        println!("{}", dp[k][i]);
    }
    dbg!(dp[k].iter().sum::<f64>());
}