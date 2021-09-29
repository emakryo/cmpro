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
        s: String,
        t: String,
    }

    if s == t {
        println!("same");
    } else {
        let s = s.to_ascii_lowercase();
        let t = t.to_ascii_lowercase();
        if s == t {
            println!("case-insensitive");
        } else {
            println!("different");
        }
    }
}