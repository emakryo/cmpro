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
        qs: [(usize, usize); m],
    }

    let mut c = vec![0; n+1];
    for (a, b) in qs {
        c[a] += 1;
        c[b] += 1;
    }

    if c.iter().all(|x| x%2==0) {
        println!("YES");
    } else {
        println!("NO");
    }
}