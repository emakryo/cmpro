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
        t: usize,
    }

    for _ in 0..t {
        solve();
    }
}

fn solve(){
    proconio::input! {
        mut a: [i64; 5],
        mut b: [i64; 5],
    }

    let k = a[4].min(b[4]);
    b[4] -= k;
    a[4] -= k;

    if a[4] > 0 {
        println!("No");
        return;
    }

    let k = a[3].min(b[3]);
    a[3] -= k;
    b[3] -= k;

    let k = a[3].min(b[4]);
    b[0] += k;
    a[3] -= k;
    b[4] -= k;

    if a[3] > 0 {
        println!("No");
        return;
    }

    let k = a[2].min(b[2]);
    a[2] -= k;
    b[2] -= k;

    let k = a[2].min(b[4]);
    b[1] += k;
    a[2] -= k;
    b[4] -= k;

    let k = a[2].min(b[3]);
    b[0] += k;
    a[2] -= k;
    b[3] -= k;

     if a[2] > 0 {
        println!("No");
        return;
    }
    dbg!(&a, &b);

    if a[0] + 2 * a[1] > b[0] + 2 * b[1] + 3 * b[2] + 4 * b[3] + 5 * b[4] {
        println!("No");
        return;
    }

    if a[1] > b[1] + b[2] + 2 * b[3] + 2 * b[4] {
        println!("No");
        return;
    }

    println!("Yes");
}