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
        s: usize,
        t: usize,
    }

    let mut ans = 0;
    for a in 0..=s {
        for b in 0..=s-a {
            for c in 0..=s-a-b {
                if a*b*c <= t {
                    ans += 1;
                }
            }
        }
    }
    println!("{}", ans);
}