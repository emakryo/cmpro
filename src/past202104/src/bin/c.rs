#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        m: usize,
        // p: usize,
        // q: usize,
        // b: [usize; p],
    }

    let mut a = vec![vec![]; n];

    for i in 0..n {
        proconio::input!{
            k: usize,
            ai: [usize; k],
        }
        a[i] = ai;
    }

    proconio::input! {
        p: usize,
        q: usize,
        b: [usize; p],
    }

    let mut ans = 0;
    for i in 0..n {
        let mut r = 0;
        for x in &a[i] {
            if b.contains(x) { r += 1; }
        }
        if r >= q { ans += 1; }
    }

    println!("{}", ans);
}