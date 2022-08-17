#![allow(unused_macros, unused_imports)]

use proconio::marker::{Chars, Usize1};
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

    for i in 0..t {
        print!("Case #{}: ", i+1);
        solve();
    }
}

fn solve() {
    proconio::input! {
        r: usize,
        c: usize,
        k: Usize1,
        g: [Chars; r],
    }

    let mut ans = g[k].iter().filter(|cc| **cc=='X').count();
    let mut cnt = vec![0; c];
    for i in (k+1)..r {
        for j in 0..c {
            if g[i][j] == 'X' {
                cnt[j] += 1;
            }
        }
    }
    let mut cum = 0;

    for i in (0..k).rev() {
        let mut x = g[i].iter().filter(|cc| **cc=='X').count() + cum + (k - i);
        for j in 0..c {
            if cnt[j] > r-k {
                x += 1;
                cum += 1;
            }
        }

        ans = ans.min(x);

        for j in 0..c {
            if g[i][j] == 'X' {
                cnt[j] += 1;
            }
        }
    }

    let mut cnt = vec![0; c];
    for i in 0..k {
        for j in 0..c {
            if g[i][j] == 'X' {
                cnt[j] += 1;
            }
        }
    }
    let mut cum = 0;
 
    for i in k+1..r {
        let mut x = g[i].iter().filter(|cc| **cc=='X').count() + cum + (i - k);
        for j in 0..c {
            if cnt[j] > k {
                x += 1;
                cum += 1;
            }
        }
        ans = ans.min(x);

        for j in 0..c {
            if g[i][j] == 'X' {
                cnt[j] += 1;
            }
        }
    }

    println!("{}", ans);
}