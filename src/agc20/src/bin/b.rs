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
        a: [i64; n],
    }

    let mut x = 2;
    let mut y = 2;
    for &ai in a.iter().rev() {
        let nx = (x + ai - 1) / ai * ai;
        let ny = y / ai * ai;
        if ny < nx {
            println!("-1");
            return;
        }

        x = nx;
        y = ny + ai - 1;
    }

    println!("{} {}", x, y);
}