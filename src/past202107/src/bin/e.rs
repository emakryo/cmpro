#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        mut n: usize,
    }

    let mut ans = None;
    let mut k = 30;
    while n > 1 {
        if n % 3 == 0 {
            n /= 3;
        } else if n % 3 == 1 {
            ans = Some(k);
            n = (n-1)/3;
        } else {
            break;
        }
        k -= 1;
    }

    if n == 1 {
        if let Some(k) = ans {
            println!("{}", k);
        } else {
            println!("-1");
        }
    } else {
        println!("-1");
    }
}