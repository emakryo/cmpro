#![allow(unused_macros, unused_imports)]

use proconio::marker::Usize1;
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
        mut a: [[usize]; m],
    }

    for i in 0..m {
        for ai in &mut a[i] {
            *ai = *ai-1;
        }
    }

    let mut pos = vec![vec![]; n];
    for i in 0..m {
        pos[a[i][0]].push(i);
    }

    let mut two = vec![];
    for i in 0..n {
        if pos[i].len() == 2 {
            two.push(i);
        }
    }

    for i in 0..m {
        a[i].reverse();
    }

    let mut total = 0;
    while let Some(i) = two.pop() {
        let p = pos[i][0];
        let q = pos[i][1];
        a[p].pop();
        a[q].pop();
        total += 1;

        if let Some(&x) = a[p].last() {
            pos[x].push(p);
            if pos[x].len() == 2 {
                two.push(x);
            }
        }

        if let Some(&x) = a[q].last() {
            pos[x].push(q);
            if pos[x].len() == 2 {
                two.push(x);
            }
        }
    }

    if total == n {
        println!("Yes");
    } else {
        println!("No");
    }

}