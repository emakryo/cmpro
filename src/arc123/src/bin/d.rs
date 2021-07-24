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
        a: [i64; n],
    }

    let mut b = vec![0];
    let mut c = vec![0];
    for i in 1..n {
        let bi = *b.last().unwrap();
        let ci = *c.last().unwrap();
        if a[i] > a[i-1] {
            b.push(bi+a[i]-a[i-1]);
            c.push(ci);
        } else {
            b.push(bi);
            c.push(ci+a[i]-a[i-1]);
        }
    }

    dbg!(&b, &c);

    for ci in c{
        b.push(-a[0]-ci);
    }

    b.sort();
    dbg!(&b);

    let x = b[n];
    let mut ans = 0;
    for bi in b {
        ans += (x-bi).abs();
    }

    println!("{}", ans);
    
}