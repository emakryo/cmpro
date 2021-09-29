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
        p: [usize; n],
    }

    let mut ans = vec![0; n];
    for (i, pi) in p.into_iter().enumerate() {
        ans[pi-1] = i+1;
    }

    println!("{}", ans.iter().map(ToString::to_string).collect::<Vec<String>>().join(" "));
}