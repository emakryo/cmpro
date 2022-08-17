#![allow(unused_macros, unused_imports)]

use std::{collections::{BTreeSet, BinaryHeap}, iter::FromIterator, cmp::Reverse};
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
        l: i64,
        mut a: [i64; n],
    }

    let s = a.iter().sum::<i64>();
    if s < l {
        a.push(l -s);
    }
    a.sort();

    let mut b = BinaryHeap::from_iter(a.into_iter().map(|x| Reverse(x)));
    let mut ans = 0;

    while b.len() > 1 {
        let x = b.pop().unwrap().0;
        let y = b.pop().unwrap().0;

        dbg!(x, y);
        b.push(Reverse(x + y));
        ans += x + y;        
    }

    println!("{}", ans);
}
