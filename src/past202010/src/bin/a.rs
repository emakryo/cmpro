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
        a: [usize; 3],
    }

    if a[0] <= a[1] && a[1] <= a[2] || a[2] <= a[1] && a[1] <= a[0] {
        println!("B");
    } else if a[1] <= a[0] && a[0] <= a[2] || a[2] <= a[0] && a[0] <= a[1] {
        println!("A");
    } else {
        println!("C");
    }

}