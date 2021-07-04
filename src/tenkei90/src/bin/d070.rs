#![allow(unused_imports)]
fn main() {
    proconio::input! {
        n: usize,
        xs: [(i64, i64); n],
    }

    let mut v:Vec<_> = xs.iter().map(|(x, _)| x).collect();
    v.sort();
    let mut u:Vec<_> = xs.iter().map(|(_, y)| y).collect();
    u.sort();

    let va = v[n/2];
    let ua = u[n/2];

    let ans: i64 = xs.iter().map(|(x, y)| (x-va).abs()+(y-ua).abs()).sum();
    println!("{}", ans);
}
