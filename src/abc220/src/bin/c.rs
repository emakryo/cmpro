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
        a: [i64; n],
        x: i64,
    }

    let s: i64 = a.iter().sum();

    let mut ans = x / s * n as i64;
    let mut x = x - x / s * s;

    for ai in a {
        x -= ai;
        ans += 1;
        dbg!(ai, x, ans);
        if x < 0 {
            break;
        }
    }

    println!("{}", ans);
}