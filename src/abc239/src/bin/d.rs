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
        a: i64,
        b: i64,
        c: i64,
        d: i64,
    }

    for x in a..=b {
        let mut win = true;
        for y in c..=d {
            if is_prime(x + y) {
                win = false;
            }
        }

        if win {
            println!("Takahashi");
            return;
        }
    }

    println!("Aoki");
}


fn is_prime(x: i64) -> bool {
    for i in 2..x {
        if i * i > x {
            break;
        }

        if x % i == 0 {
            return false;
        }
    }

    true
}