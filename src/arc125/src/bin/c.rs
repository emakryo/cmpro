#![allow(unused_macros, unused_imports)]

use std::collections::{BTreeSet, BinaryHeap};
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
        k: usize,
        a: [usize; k],
    }

    let mut ans = vec![];
    let mut xs = BTreeSet::new();
    for i in 1..=n {
        xs.insert(i);
    }
    for &ai in &a {
        xs.remove(&ai);
    }
    for i in 0..a.len()-1 {
        ans.push(a[i]);
        if let Some(&x) = xs.iter().next() {
            if x < a[i] {
                xs.remove(&x);
                ans.push(x);
            }
        }
    }
    xs.insert(a[a.len()-1]);
    for x in xs.iter().rev() {
        ans.push(*x);
    }

    println!("{}", ans.iter().map(ToString::to_string).collect::<Vec<_>>().join(" "));

}