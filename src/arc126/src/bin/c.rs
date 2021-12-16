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
        k: usize,
        mut a: [usize; n],
    }

    a.sort();
    let mut c = vec![0; n+1];
    for i in 0..n {
        c[i+1] = c[i] + a[i];
    }

    let mut ans = 0;
    for i in 1..=a[n-1] {
        let mut s = 0;
        let mut j = 0;
        for k in 0..=a[n-1]{ // i*k ~ i*(k+1)
            if i*k > a[n-1] {
                break;
            }
            // let p = a.binary_search(&(i*(k+1)+1)).unwrap_or_else(|x| x);
            let p;
            let x = i*(k+1)+1;

            if x <= a[0] {
                p = 0;
            } else {
                let mut ok = n;
                let mut ng = 0;
                while ok - ng > 1 {
                    let mid = (ok + ng) / 2;
                    if a[mid] >= x {
                        ok = mid;
                    } else {
                        ng = mid;
                    }
                }
                p = ok;
            }

            let t = c[p] - c[j];
            dbg!(i, k, i*(k+1)+1, j, p, t);
            s += i*(k+1)*(p-j) - t;
            j = p;
        }
        // dbg!(i, s);

        if s <= k {
            ans = i;
        }
    }

    if n * a[n-1] - c[n] <= k {
        let p = k + c[n] - n * a[n-1];
        ans = a[n-1] + p / n;
    }

    println!("{}", ans);
}