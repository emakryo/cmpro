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

    let ans = rec(n);
    println!("{}", ans.len());
    for a in ans {
        println!("{}", a);
    }
}

fn rec(n: usize) -> Vec<String> {
    let mut ret: Vec<String> = vec!["A".repeat(1<<n-1) + &"B".repeat(1<<n-1)];
    if n == 1 {
        return ret;
    }

    for x in rec(n-1) {
        let y = x.chars().map(|c| {
            match c {
                'A' => 'B',
                'B' => 'A',
                _ => panic!(),
            }
        }).collect::<String>();

        ret.push(format!("{}{}", x, x));
        ret.push(format!("{}{}", x, y));
    }

    ret
}