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

fn lower_bound(a: &[usize], x: usize) -> usize {
    if x <= a[0] { return 0; }
    let mut lb = 0;
    let mut ub = a.len();
    while ub - lb > 1 {
        let m = (ub+lb) / 2;
        if a[m] < x {
            lb = m;
        } else {
            ub = m;
        }
    }

    return ub;
}

fn main() {
    proconio::input!{
        n: usize,
        mut a: [usize; n],
        mut b: [usize; n],
        mut c: [usize; n],
    }

    a.sort();
    b.sort();
    c.sort();
    dbg!(&a, &b, &c);

    let mut b0 = 0;
    let mut c0 = 0;

    let mut ans = 0;
    for i in 0..n {
        let j = lower_bound(&b[b0..], a[i]+1);
        if b0+j < n {
            let k = lower_bound(&c[c0..], b[b0+j]+1);
            if c0+k < n {
                ans += 1;
                dbg!(i, b0+j, c0+k, a[i], b[b0+j], c[c0+k]);
                b0 += j+1;
                c0 += k+1;
            }
        }
        if b0 >= n || c0 >= n {
            break;
        }
    }

    println!("{}", ans);
}