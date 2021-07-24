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
        es: [(f64, f64); 2],
        ps: [(f64, f64); n],
    }

    let t = - (es[1].1 - es[0].1).atan2(es[1].0 - es[0].0);
    let l = {
        let (x, y) = (es[1].0-es[0].0, es[1].1-es[0].1);
        dbg!(x, y);
        (x * t.cos() - y * t.sin(), x * t.sin() + y * t.cos())
    };
    let dx = -l.0 / 2.0;
    dbg!(l, dx, t);
    let ps: Vec<_> = ps.into_iter().map(|(x, y)| {
        let (x, y) = (x-es[0].0, y-es[0].1);
        (x * t.cos() - y * t.sin() + dx, x * t.sin() + y * t.cos())
    }).collect();

    for (x, y) in ps {
        println!("{} {}", x, y);
    }

}