#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        s: String,
    }

    let mut ok = true;
    for (i, c) in s.chars().enumerate() {
        if i == 3 {
            ok = ok && c == '-';
        } else {
            ok = ok && c != '-';
        }
    }
    if ok {
        println!("Yes");
    } else {
        println!("No");
    }
}