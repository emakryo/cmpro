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
        mut b: [usize; n],
    }

    b.sort();

    if n == 2 {
        println!("{}", (b[0] + b[1]) / 2);
        return;
    }

    let d = (b[1] - b[0]).min(b[n-1] - b[n-2]);

    for i in 0..n-1 {
        if b[i] + d != b[i+1] {
            println!("{}", b[i] + d);
        }
    }
}
