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
    }

    let mut a = vec![1; n];

    for i in 0..n {
        for j in 2..=n {
            let k = (i+1)*j-1;
            dbg!(i, k);
            if k >= n { break; }
            if a[k] == a[i] {
                a[k]+=1;
            }
        }
    }

    println!("{}", a.iter().map(i32::to_string).collect::<Vec<_>>().join(" "));
}