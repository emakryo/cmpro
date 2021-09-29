#![allow(unused_macros, unused_imports)]

use std::{collections::{BTreeMap, BTreeSet}, iter::FromIterator};
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
        s: [i64; n],
        t: [i64; n],
    }

    let mut x = t.clone();
    let mut c = 0;
    for i in (1..n).rev() {
        c += s[i];
        x[i] += c;
    }

    let mut q = BTreeMap::new();
    for &xi in &x {
        *q.entry(xi).or_insert(0) += 1;
    }
    let mut offset = 0;
    // dbg!(&q);
    for i in 0..n {
        let a = q.range(..).next().unwrap().0;
        println!("{}", a + offset);

        if i < n-1 {
            *q.get_mut(&x[i+1]).unwrap() -= 1;
            offset += s[i];
            *q.entry(t[i+1]-offset).or_default() += 1;
            x[i+1] = t[i+1]-offset;
            // dbg!(&q);
        }
    }
}