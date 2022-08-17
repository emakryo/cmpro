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

fn main() {
    proconio::input!{
        n: usize,
        w: usize,
        a: [usize; n],
    }

    let mut x = vec![false; w+1];
    for i in 0..n {
        if a[i] <= w {
            x[a[i]] = true;
        }
        for j in i+1..n {
            if a[i] + a[j] <= w {
                x[a[i]+a[j]] = true;
            }
            for k in j+1..n {
                if a[i] + a[j] + a[k] <= w {
                    x[a[i]+a[j]+a[k]] = true;
                }
            }
        }
    }

    let ans = x.into_iter().filter(|x| *x).count();
    println!("{}", ans);
}