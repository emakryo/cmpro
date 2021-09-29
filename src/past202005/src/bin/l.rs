#![allow(unused_macros, unused_imports)]

use std::collections::{BTreeMap, HashMap, VecDeque};
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
        t: [[usize]; n],
        m: usize,
        a: [usize; m],
    }

    let mut t = t.into_iter().map(|ti| {
        ti.into_iter().collect::<VecDeque<_>>()
    }).collect::<Vec<_>>();

    let mut x1 = BTreeMap::new();
    let mut x2 = BTreeMap::new();

    for i in 0..n {
        x1.insert(t[i][0], i);
        x2.insert(t[i][0], i);
        if t[i].len() >= 2 {
            x2.insert(t[i][1], i);
        }
    }

    for ai in a {
        if ai == 1 {
            let (&x, &k) = x1.iter().rev().next().unwrap();
            println!("{}", x);
            x1.remove(&x);
            x2.remove(&x);
            t[k].pop_front();

            if t[k].len() > 0 {
                x1.insert(t[k][0], k);
            }
            if t[k].len() > 1 {
                x2.insert(t[k][1], k);
            }
        } else {
            let (&x, &k) = x2.iter().rev().next().unwrap();

            println!("{}", &x);
            x1.remove(&x);
            x2.remove(&x);
            if t[k][0] == x {
                t[k].pop_front();
            } else {
                let t0 = t[k].pop_front().unwrap();
                t[k].pop_front();
                t[k].push_front(t0);
            }

            if t[k].len() > 0 {
                x1.insert(t[k][0], k);
                x2.insert(t[k][0], k);
            }
            if t[k].len() > 1 {
                x2.insert(t[k][1], k);
            }
        }
    }
}