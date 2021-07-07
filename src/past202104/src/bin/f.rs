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
        l: usize,
        t: usize,
        x: usize,
        xs: [(usize, usize); n],
    }
    let mut s = 0;
    let mut ans = 0;
    for (a, b) in xs {
        if  a > t && b >= l {
            println!("forever");
            return;
        }
        if b < l {
            ans += a;
            s = 0;
        } else if s + a == t {
            ans += a + x;
            s = 0;
        } else if s + a > t {
            if a < t {
                ans += t - s + x + a;
                s = a;
            } else {
                ans += t - s + x + a + x;
                s = 0;
            }
        } else {
            ans += a;
            s += a;
        }
        dbg!(a, b, ans);
    }

    println!("{}", ans);
}