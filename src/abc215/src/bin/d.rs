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
        m: usize,
        a: [usize; n],
    }

    let l = 100001;
    let mut sieve = vec![false; l];
    sieve[0] = true;
    sieve[1] = true;
    for i in 2..l {
        if sieve[i] { continue }
        for j in 2..l {
            if i*j >= l { break }
            sieve[i*j] = true;
        }
    }

    let mut p = vec![];
    for i in 2..l {
        if !sieve[i] {
            p.push(i);
        }
    }

    dbg!(&p[..10], p.len());
    let mut pb = vec![false; p.len()];

    for mut ai in a {
        for (i, &pi) in p.iter().enumerate() {
            if pi*pi > ai {
                break;
            }
            while ai % pi == 0 {
                ai /= pi;
                pb[i] = true;
            }
        }

        if ai != 1 {
            let k = p.binary_search(&ai).unwrap();
            pb[k] = true;
        }
    }

    let mut ans = vec![true; m+1];
    ans[0] = false;
    for i in 0..p.len() {
        if pb[i] {
            for j in 1..m {
                if p[i]*j > m { break }
                ans[p[i]*j] = false;
            }
        }
    }

    println!("{}", ans.iter().filter(|&&x| x).count());
    for i in 0..=m {
        if ans[i] {
            println!("{}", i);
        }
    }
}