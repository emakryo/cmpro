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
        xs: [(i64, i64, i64, i64, i64); t],
    }

    for (n, ax, bx, ay, by) in xs {
        let mut ans;
        if bx == by {
            if ax == ay {
                ans = n;
            } else {
                ans = 0;
            }
        } else {
            let (ax, bx, ay, by) = if bx > by {
                (ay, by, ax, bx)
            } else {
                (ax, bx, ay, by)
            };

            let ymin = ax.max(ay);
            let ymax = (ax+n/bx).min(ay+n/by)+1;
            dbg!(ymin, ymax);
            if ymax <= ymin {
                ans = 0;
            } else {
                let mut lb = ymin-1;
                let mut ub = ymax;
                while ub - lb > 1 {
                    let y = (ub+lb)/2;
                    if by * (y-ay+1) <= bx * (y-ax) {
                        lb = y;
                    } else {
                        ub = y;
                    }
                }

                ans = 0;
                for y in ub..ymax {
                    let k = (n+1).min(bx*(y-ax+1)).min(by*(y-ay+1)) - 1.max(by*(y-ay)).max(bx*(y-ax));
                    dbg!(y, bx*(y-ax), bx*(y-ax+1), by*(y-ay), by*(y-ay+1), k);
                    if k <= 0 {
                        break;
                    }
                    ans += k;
                }
            }
        }

        println!("{}", ans);
    }
}