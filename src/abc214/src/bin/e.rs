#![allow(unused_macros, unused_imports)]

use std::collections::BTreeMap;
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
        t: usize,
    }

    for _ in 0..t {
        solve();
    }
}

fn solve() {
    proconio::input! {
        n: usize,
        mut xs: [(usize, usize); n],
    }

    xs.sort_by_key(|&(_, r)| r);
    let mut rs = BTreeMap::<usize, usize>::new();

    for (l, r) in xs {
        if let Some((&rr, &rl)) = rs.range(l..).next() {
            if l < rl {
                let x = if l == rl-1 {
                    *rs.get_mut(&rr).unwrap() = l;
                    rr
                } else {
                    rs.insert(l, l);
                    l
                };
                if let Some((&lr, &ll)) = rs.range(..l).rev().next() {
                    if lr == l-1 {
                        rs.remove(&lr);
                        *rs.get_mut(&x).unwrap() = ll;
                    }
                }
            } else if rr < r {
                rs.remove(&rr);
                rs.insert(rr+1, rl);

                if let Some((&sr, &sl)) = rs.range(rr+2..).next() {
                    if rr+2 == sl {
                        rs.remove(&(rr+1));
                        *rs.get_mut(&sr).unwrap() = rl;
                    }
                }
            } else {
                println!("No");
                return;
            }
        } else {
            if let Some(&ll) = rs.get(&(l-1)) {
                rs.remove(&(l-1));
                rs.insert(l, ll);
            } else {
                rs.insert(l, l);
            }
        }
        dbg!(&rs);
    }

    println!("Yes");
}