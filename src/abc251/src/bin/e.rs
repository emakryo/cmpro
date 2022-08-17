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
        a: [u64; n],
    }

    let inf = 1000000000000u64;
    let mut dp1 = vec![inf; n+1];
    dp1[0] = 0;

    for i in 0..n-1 {
        dp1[i+2] = a[i] + dp1[i].min(dp1[i+1]);
    }
    dbg!(&dp1);

    let mut dp2 = vec![inf; n+1];
    dp2[1] = 0;
    for i in 1..n-1 {
        dp2[i+2] = a[i] + dp2[i].min(dp2[i+1]);
    }
    dbg!(&dp2);

    println!("{}", dp1[n]
        .min(dp1[n-1] + a[n-2].min(a[n-1]))
        .min(dp2[n-1] + a[n-1].min(a[0] + a[n-2]))
        .min(dp2[n] + a[0].min(a[n-1]))
    );

}