#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        mut x: i32,
        a: [i32; n],
    }

    for i in 0..n {
        if i%2 == 0 {
            x -= a[i];
        } else {
            x -= a[i]-1;
        }
    }

    if x >= 0 {
        println!("Yes");
    } else {
        println!("No");
    }
}