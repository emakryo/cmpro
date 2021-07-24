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
        a: [isize; 3],
    }

    let ans = if a[0]+a[2] <= 2*a[1] {
        2*a[1]-a[0]-a[2]
    } else if (a[0]+a[2])%2 == 0 {
        (a[0]+a[2])/2 - a[1]
    } else {
        (a[0]+a[2]+1)/2 - a[1] + 1
    };

    println!("{}", ans);
}