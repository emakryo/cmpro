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
        x: u64,
        y: u64,
        a: u64,
        b: u64,
        c: u64,
    }

    if a + b + c > x * y {
        println!("No");
        return;
    }

    if check(x, y, a, b, c) || check(x, y, b, a, c) || check(x, y, c, a, b) {
        println!("Yes");
    } else {
        println!("No");
    }
}

fn check(x: u64, y: u64, a: u64, b: u64, c: u64) -> bool {
    if (a + y - 1) / y < x {
        let xa =  x - (a + y - 1) / y;

        if (b + y - 1) / y < xa && (xa - (b + y -1) / y) * y >= c {
            return true;
        }

        if (b + xa - 1) / xa < y && (y - (b + xa - 1) / xa) * xa >= c {
            return true;
        }
    }

    if (a + x - 1) / x < y {
        let ya = y - (a + x - 1) / x;

        if (b + ya - 1) / ya < x && (x - (b + ya - 1) / ya) * ya >= c {
            return true;
        }

        if (b + x - 1) / x < ya && (ya - (b + x - 1) / x) * x >= c {
            return true;
        }
    }

    return false;
}