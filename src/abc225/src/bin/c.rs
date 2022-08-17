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
        m: usize,
        b: [[usize; m]; n],
    }

    let mut ok = true;
    for i in 0..n {
        for j in 0..m {
            if i > 0 {
                if b[i-1][j] + 7 != b[i][j] {
                    ok = false;
                }
            }
            if j > 0 {
                if b[i][j-1] + 1 != b[i][j] {
                    ok = false;
                }
                if (b[i][j-1] - 1) / 7 != (b[i][j] - 1) / 7 {
                    ok = false;
                }
            }
        }
    }

    if ok {
        println!("Yes");
    } else{
        println!("No");
    }
}