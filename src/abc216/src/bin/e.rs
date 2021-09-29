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
        mut k: usize,
        mut a: [usize; n],
    }

    a.push(0);
    a.sort();

    let mut ans = 0;

    for i in (0..n).rev() {
        let l = n-i;

        if l * (a[i+1] - a[i]) <= k {
            ans += l * (a[i]+ 1 + a[i+1]) * (a[i+1] - a[i]) / 2;
            k -= l * (a[i+1]-a[i]);
        } else {
            let m = k / l;
            ans += l * (a[i+1] - m + 1 + a[i+1]) * m / 2 + (k % l) * (a[i+1] - m);
            break;
        }
    }

    println!("{}", ans);
}