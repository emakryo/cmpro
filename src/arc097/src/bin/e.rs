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
        xs: [(char, usize); 2*n],
    }

    let mut cb = vec![vec![0; n+1]; 2*n+1];
    let mut cw = vec![vec![0; n+1]; 2*n+1];
    let mut ib = vec![0; n+1];
    let mut iw = vec![0; n+1];

    for (i, &(c, a)) in xs.iter().enumerate().rev() {
        cb[i] = cb[i+1].clone();
        cw[i] = cw[i+1].clone();
        if c == 'B' {
            for k in a..=n {
                cb[i][k] += 1;
            }
            ib[a] = i;
        } else {
            for k in a..=n {
                cw[i][k] += 1;
            }
            iw[a] = i;
        }

    }


    let inf = 1000000000;
    let mut dp = vec![vec![inf; n+1]; n+1];

    dp[0][0] = 0;
    for i in 0..=n {
        for j in 0..=n {
            if i > 0 {
                let k = ib[i];
                dp[i][j] = dp[i][j].min(dp[i-1][j] + k + cw[k][j] + cb[k][i] - (i+j));
            }
            if j > 0 {
                let k = iw[j];
                dp[i][j] = dp[i][j].min(dp[i][j-1] + k + cw[k][j] + cb[k][i] - (i+j));
            }
        }
    }

    println!("{}", dp[n][n]);
}