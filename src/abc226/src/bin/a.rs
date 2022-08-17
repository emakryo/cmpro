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
    }

    let a = s.split('.').map(|x| x.parse::<u64>().unwrap()).collect::<Vec<_>>();
    if a[1] >= 500 {
        println!("{}", a[0]+1);
    } else {
        println!("{}", a[0]);
    }
}