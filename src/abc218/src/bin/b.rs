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
        p: [usize; 26],
    }

    let ans = p.iter().map(|i| (b'a' + *i as u8 - 1) as char).collect::<String>();
    println!("{}", ans);
}