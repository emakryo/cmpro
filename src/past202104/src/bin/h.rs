#![allow(unused_macros)]

use std::collections::BinaryHeap;
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        m: usize,
        k: usize,
        q: usize,
        xs: [(usize, usize); n],
    }

    let mut a = vec![];
    let mut b= vec![];
    for (p, t) in xs {
        if t==0 { a.push(p); }
        else { b.push(p); }
    }
    a.sort();
    b.sort();

    let mut que = BinaryHeap::new();
    let mut total = 0;
    for &p in &a[0..m.min(a.len())] {
        que.push(p);
        total += p;
    }

    let mut ans = std::usize::MAX;
    if que.len() == m {
        ans = ans.min(total);
    }

    for i in 0..(b.len()+k-1)/k {
        for j in k*i..(k*(i+1)).min(b.len()) {
            que.push(b[j]);
            total += b[j];
        }

        while que.len() > m {
            let x = que.pop();
            total -= x.unwrap();
        }

        if que.len() == m {
            ans = ans.min(total + q * (i+1));
        }
        // dbg!(i, total, ans, &que);
    }

    println!("{}", ans);
}