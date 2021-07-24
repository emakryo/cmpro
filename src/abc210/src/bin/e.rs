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

fn gcd(x: usize, y: usize) -> usize {
    if y == 0 { x }
    else { gcd(y, x%y) }
}

fn main() {
    proconio::input!{
        mut n: usize,
        m: usize,
        mut es: [(usize, usize); m],
    }

    es.sort_by_key(|x| x.1);

    let mut ans = 0;
    for i in 0..m {
        let g = gcd(n, es[i].0);

        let k = n / g;
        ans += g * (k-1) * es[i].1;
        dbg!(es[i].0, es[i].1, g, k);
        n = g;
        if n == 1 {
            println!("{}", ans);
            return;
        }
    }

    println!("{}", -1);

}