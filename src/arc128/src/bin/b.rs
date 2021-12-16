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
        xs: [[i64; 3]; t],
    }

    let inf = i64::max_value();
    for mut xss in xs {
        xss.sort();
        let r = xss[0];
        let g = xss[1];
        let b = xss[2];

        let mut ans = inf;

        if r == g {
            ans = ans.min(r);
        }
        if g == b {
            ans = ans.min(g);
        }

        if (g-r) % 3 == 0 {
            ans = ans.min(g);
        }

        if (b-r) % 3 == 0 || (b-g) % 3 == 0 {
            ans = ans.min(b);
        }

        println!("{}", if ans == inf { -1 } else { ans });
    }
    
}