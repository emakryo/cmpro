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
    }

    let mut l = 0.0;
    for i in 1..=n {
        l += (i as f64).log10();
    }
    dbg!(l);
    println!("{}", 1 + (l.floor() as i64));
}