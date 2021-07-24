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
        y: usize,
    }

    if y == 0 {
        println!("ERROR");
    } else {
        println!("{}.{:02}", x/y, 100*(x%y)/y);
    }
}