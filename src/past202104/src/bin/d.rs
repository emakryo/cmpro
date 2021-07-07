#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

#[proconio::fastout]
fn main() {
    proconio::input!{
        n: usize,
        k: usize,
        a: [i64; n],
    }

    let mut ans = 0;
    for i in 0..k {
        ans += a[i];
    }

    println!("{}", ans);

    for i in 0..n-k {
        ans += a[i+k] - a[i];
        println!("{}", ans);
    }
}