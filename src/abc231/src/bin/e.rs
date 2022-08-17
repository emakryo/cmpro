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
        x: i64,
        a: [i64; n],
    }

    let mut c = vec![0; n];
    for i in 0..n-1 {
        c[i] = x % a[i+1] / a[i];
    }
    c[n-1] = x / a[n-1];
    dbg!(&c);

    let inf = 1<<62;
    let mut dp = vec![(0, inf); n];
    for i in 0..n-1 {
        let k = a[i+1] / a[i];
        dp[i+1].0 = (c[i] + dp[i].0).min(c[i] + 1 + dp[i].1);
        dp[i+1].1 = (k - c[i]  + dp[i].0).min(k - c[i] - 1 + dp[i].1);
        dbg!(dp[i+1]);
    }

    let ans = (c[n-1] + dp[n-1].0).min(c[n-1] + 1 + dp[n-1].1);

    println!("{}", ans);
}
