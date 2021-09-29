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
        m: usize,
        n: usize,
        a: [[usize; n]; m],
    }

    let ans = a.iter().map(|xs| xs.iter().sum::<usize>()).max().unwrap();
    println!("{}", ans);
}