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
        x: i64,
    }

    println!("{}", if x < 0 {
        (x + 1) / 10 - 1
    } else {
        x / 10
    });
}
