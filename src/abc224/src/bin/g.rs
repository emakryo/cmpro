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
        n: i64,
        s: i64,
        t: i64,
        a: f64,
        b: f64,
    }

    let f = |k: f64| {
        a * k * 0.5 + n as f64 * b / k - a * 0.5
    };
    dbg!(f(1.0), f(2.0), f(3.0));

    let k = (2.0 * n as f64 * b / a).sqrt() as i64;

    let mut ans: f64 = f(1.0).min(f(t as f64));
    if s <= t {
        ans = ans.min((t-s) as f64 * a);
    }
    for i in (k-3).max(1)..(k+3).min(t+1) {
        ans = ans.min(f(i as f64));
    }
    println!("{}", ans);
}