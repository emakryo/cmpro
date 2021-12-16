#![allow(unused_macros, unused_imports)]

use proconio::marker::Bytes;
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
        s: [Bytes; n],
        t: [Bytes; n],
    }

    let mut sx_min = n;
    let mut sx_max = 0;
    let mut sy_min = n;
    let mut sy_max = 0;

    let mut tx_min = n;
    let mut tx_max = 0;
    let mut ty_min = n;
    let mut ty_max = 0;

    for i in 0..n {
        for j in 0..n {
            if s[i][j] == b'#' {
                sx_min = sx_min.min(i);
                sx_max = sx_max.max(i);
                sy_min = sy_min.min(j);
                sy_max = sy_max.max(j);
            }

            if t[i][j] == b'#' {
                tx_min = tx_min.min(i);
                tx_max = tx_max.max(i);
                ty_min = ty_min.min(j);
                ty_max = ty_max.max(j);
            }
        }
    }

    let sdx = sx_max - sx_min;
    let sdy = sy_max - sy_min;
    let tdx = tx_max - tx_min;
    let tdy = ty_max - ty_min;

    if (sdx, sdy) == (tdx, tdy) {
        let mut ok = true;
        for i in sx_min..sx_max {
            for j in sy_min..sy_max {
                if s[i][j] != t[i+tx_min-sx_min][j+ty_min-sy_min] {
                    ok = false;
                }
            }
        }
        if ok {
            println!("Yes");
            return;
        }

        let mut ok = true;
        for i in sx_min..sx_max {
            for j in sy_min..sy_max {
                if s[i][j] != t[tx_max+sx_min-i][ty_max+sy_min-j] {
                    ok = false;
                }
            }
        }
        if ok {
            println!("Yes");
            return;
        }
    }

    if (sdx, sdy) == (tdy, tdx) {
        let mut ok = true;
        for i in sx_min..sx_max {
            for j in sy_min..sy_max {
                if s[i][j] != t[tx_max+sy_min-j][i+ty_min-sx_min] {
                    ok = false;
                }
            }
        }
        if ok {
            println!("Yes");
            return;
        }

        let mut ok = true;
        for i in sx_min..sx_max {
            for j in sy_min..sy_max {
                if s[i][j] != t[j+tx_min-sy_min][ty_max+sx_min-i] {
                    ok = false;
                }
            }
        }
        if ok {
            println!("Yes");
            return;
        }
     }

    println!("No");
    
}