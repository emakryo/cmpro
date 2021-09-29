#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

use itertools::Itertools;

fn main() {
    proconio::input!{
        n: usize,
        mut a: [usize; n],
    }

    a.sort();
    
    let mut ans = 0;
    for i in 5..n {
        for c in 0..1<<6 {
            let mut is = vec![];
            let mut js = vec![];

            for i in 0..6 {
                if c>>i&1 == 1 {
                    is.push(i);
                } else {
                    js.push(i);
                }
            }

            if is.len() != 3 {
                continue;
            }
            if a[i-is[2]] + a[i-is[1]] > a[i-is[0]] && a[i-js[2]] + a[i-js[1]] > a[i-js[0]] {
                ans = ans.max(a[i-5..i+1].iter().sum::<usize>());
            }
        }
    }

    let mut xs = vec![0; n];
    for i in 2..n {
        if a[i-2] + a[i-1] > a[i] {
            xs[i] = a[i-2] + a[i-1] + a[i];
        }
    }

    for i in 5..n {
        if xs[i] > 0 && xs[i-3] > 0 {
            ans = ans.max(xs[i] + xs[i-3]);
        }
        xs[i-2] = xs[i-2].max(xs[i-3]);
    }

    dbg!(&a);
    dbg!(&xs);
    println!("{}", ans);
}