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
        x: [(String, String); n],
    }

    fn parse(s: &String) -> i64 {
        let h: i64 = s[0..2].parse().unwrap();
        let m: i64 = s[3..5].parse().unwrap();
        let sec: i64 = s[6..8].parse().unwrap();
        let msec: i64 = s[9..12].parse().unwrap();
        msec + 1000 * (sec + 60 * (m + 60 * (h-21)))
    }

    let x: Vec<_> = x.iter().map(|(a, b)| (parse(a), parse(b))).collect();

    let mut r = None;
    for &(s, e) in &x {
        if e <= s {
            if let Some((a, b)) = &mut r {
                *a = s.max(*a);
                *b = (e+1000).min(*b);
            } else {
                r = Some((s, e+1000));
            }
        }
    }

    dbg!(r);

    for (s, e) in x {
        if e <= s {
            println!("{}", e+1000 - s);
        } else {
            if let Some((a, b)) = r {
                if e <= a - 1000{
                    println!("{}", e - s);
                } else if s <= a - 1000 && b <= e {
                    println!("{}", e - s + 1000);
                } else if b <= s {
                    println!("{}", e - s);
                } else {
                    println!("-1");
                }

            } else {
                println!("-1");
            }
        }
    }
}