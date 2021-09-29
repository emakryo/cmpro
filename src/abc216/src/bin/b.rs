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
        xs: [(String, String); n],
    }

    for i in 0..n {
        for j in i+1..n {
            if xs[i] == xs[j] {
                println!("Yes");
                return;
            }
        }
    }

    println!("No");
}