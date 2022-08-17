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
        a: [usize; 4*n-1],
    }

    let mut c = vec![0; n];
    for &x in &a {
        c[x-1] += 1;
    }

    for i in 0..n {
        if c[i] == 3 {
            println!("{}", i+1);
        }
    }
}