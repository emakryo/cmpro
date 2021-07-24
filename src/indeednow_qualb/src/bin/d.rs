#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {
    proconio::input!{
        n: usize,
        c: usize,
        a: [usize; n],
    }

    let mut idx = vec![vec![]; c];
    for (i, x) in a.iter().enumerate() {
        idx[x-1].push(i+1);
    }

    for i in 0..c {
        let mut l = 0;
        let mut ans = 0usize;

        for &j in &idx[i] {
            ans += (j-l) * (n-j+1);
            l = j;
        }

        println!("{}", ans);
    }

}