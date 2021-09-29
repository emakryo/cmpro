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
        a: [usize; n],
    }

    let mut b = a.clone();
    b.sort();
    println!("{}", a.iter().enumerate().find(|x| x.1 == &b[n-2]).unwrap().0 + 1);
}