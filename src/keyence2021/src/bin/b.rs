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
        mut k: usize,
        a: [usize; n],
    }

    let mut x = vec![0; n];
    for ai in a {
        x[ai] += 1;
    }

    let mut ans = 0;
    for i in x {
        k = k.min(i);
        ans += k;
    }

    println!("{}", ans);
}