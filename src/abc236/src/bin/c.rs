#![allow(unused_macros, unused_imports)]

use std::collections::HashSet;
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
        s: [String; n],
        t: [String; m],
    }

    let t = t.into_iter().collect::<HashSet<String>>();
    for x in &s {
        if t.contains(x) {
            println!("Yes");
        } else {
            println!("No");
        }
    }

}