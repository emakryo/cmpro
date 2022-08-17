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
        q: usize,
    }

    let mut prev = vec![None; n];
    let mut next = vec![None; n];

    for _ in 0..q {
        proconio::input! { t:usize }

        if t == 1 {
            proconio::input! { x: Usize1, y: Usize1 }
            prev[y] = Some(x);
            next[x] = Some(y);
        } else if t == 2 {
            proconio::input! { x: Usize1, y: Usize1 }
            prev[y] = None;
            next[x] = None;
        } else {
            proconio::input! { x: Usize1 }

            let mut ans = vec![x+1];
            let mut y = x;
            while let Some(z) = prev[y] {
                ans.push(z+1);
                y = z;
            }
            ans.reverse();
            y = x;
            while let Some(z) = next[y] {
                ans.push(z+1);
                y = z;
            }

            println!("{} {}", ans.len(), ans.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(" "));
        }
    }
}