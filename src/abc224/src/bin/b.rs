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
        h: usize,
        w: usize,
        a: [[u64; w]; h],
    }

    for i1 in 0..h {
        for i2 in i1+1..h {
            for j1 in 0..w {
                for j2 in j1+1..w {
                    if a[i1][j1] + a[i2][j2] > a[i2][j1] + a[i1][j2] {
                        println!("No");
                        return;
                    }
                }
            }
        }
    }
    println!("Yes");
}