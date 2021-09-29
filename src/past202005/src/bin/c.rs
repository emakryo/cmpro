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
        a: u64,
        r: u64,
        n: u64,
    }

    if r == 1 {
        println!("{}", a);
    } else {
        let mut x = a;
        for _ in 0..n-1 {
            x *= r;
            if x > 10u64.pow(9) {
                println!("large");
                return;
            }
        }

        println!("{}", x);
    }
}