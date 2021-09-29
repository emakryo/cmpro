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
        s: [String; 3],
    }

    for &x in &["ABC", "ARC", "AGC", "AHC"] {
        if !s.contains(&x.to_owned()) {
            println!("{}", x);
        }
    }
}