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
        mut s: [String; 4],
    }

    s.sort();
    let mut x: Vec<String> = ["H", "2B", "3B", "HR"].iter().map(|x| x.to_string()).collect();
    x.sort();
    if s == x {
        println!("Yes");
    } else {
        println!("No");
    }
}