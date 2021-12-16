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
        p: usize,
        a: [usize; n],
    }

    let ans = a.iter().filter(|&&a| a < p).count();

    println!("{}", ans);
}