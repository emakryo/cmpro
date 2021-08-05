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
        a: usize,
        b: usize,
    }

    println!("{}", match (a, b) {
        _ if a == 0 => "Silver",
        _ if b == 0 => "Gold",
        _ => "Alloy",
    });
}