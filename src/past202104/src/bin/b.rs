#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        s: proconio::marker::Bytes,
    }

    let mut ans = None;
    for i in 0..(s.len()/4) {
        if &s[(4*i)..(4*(i+1))] == "post".as_bytes() {
            ans = Some(i+1);
        }
    }
    if let Some(x) = ans {
        println!("{}", x);
    } else {
        println!("none");
    }
}