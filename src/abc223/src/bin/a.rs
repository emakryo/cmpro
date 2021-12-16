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
        x: usize,
    }

    if x > 0 && x % 100 == 0 {
        println!("Yes");
    } else {
        println!("No");
    }
}