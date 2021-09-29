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
        h: usize,
        w: usize,
        b: [[i64; w]; h],
    }

    let mut low = vec![i64::min_value(); h];
    let mut high = vec![i64::min_value(); h];
    let mut right = vec![i64::min_value(); w];
    let mut left = vec![i64::min_value(); w];

    let mut xs = vec![vec![0; w]; w];

    for i in 0..h {
        let mut c = b[i].clone();
        for j in 1..w {
            c[j] += c[j-1];
        }
        let mut y = i64::min_value();
        for j0 in 0..w {
            for j1 in j0..w {
                let x = c[j1] - if j0 > 0 { c[j0-1] } else { 0 };
                xs[j0][j1] += x;
                y = y.max(xs[j0][j1]);
                if xs[j0][j1] < 0 {
                    xs[j0][j1] = 0;
                }
            }
        }

        low[i] = y;

        if i > 0 {
            low[i] = low[i].max(low[i-1]);
        }
    }

    let mut xs = vec![vec![0; w]; w];
    for i in (0..h).rev() {
        let mut c = b[i].clone();
        for j in 1..w {
            c[j] += c[j-1];
        }
        let mut y = i64::min_value();
        for j0 in 0..w {
            for j1 in j0..w {
                let x = c[j1] - if j0 > 0 { c[j0-1] } else { 0 };
                xs[j0][j1] += x;
                y = y.max(xs[j0][j1]);
                if xs[j0][j1] < 0 {
                    xs[j0][j1] = 0;
                }
            }
        }

        high[i] = y;
        if i < h-1 {
            high[i] = high[i].max(high[i+1]);
        }
    }

    let mut xs = vec![vec![0; h]; h];
    for i in 0..w {
        let mut c: Vec<_> = b.iter().map(|x| x[i]).collect();
        for j in 1..h {
            c[j] += c[j-1];
        }
        let mut y = i64::min_value();
        for j0 in 0..h {
            for j1 in j0..h {
                let x = c[j1] - if j0 > 0 { c[j0-1] } else { 0 };
                xs[j0][j1] += x;
                y = y.max(xs[j0][j1]);
                if xs[j0][j1] < 0 {
                    xs[j0][j1] = 0;
                }
            }
        }

        left[i] = y;
        if i > 0 {
            left[i] = left[i].max(left[i-1]);
        }
    }

    let mut xs = vec![vec![0; h]; h];
    for i in (0..w).rev() {
        let mut c: Vec<_> = b.iter().map(|x| x[i]).collect();
        for j in 1..h {
            c[j] += c[j-1];
        }
        let mut y = i64::min_value();
        for j0 in 0..h {
            for j1 in j0..h {
                let x = c[j1] - if j0 > 0 { c[j0-1] } else { 0 };
                xs[j0][j1] += x;
                y = y.max(xs[j0][j1]);
                if xs[j0][j1] < 0 {
                    xs[j0][j1] = 0;
                }
            }
        }

        right[i] = y;
        if i < w-1 {
            right[i] = right[i].max(right[i+1]);
        }
    }

    dbg!(&low, &high, &left, &right);

    let mut ans = i64::min_value();
    for i in 0..h-1 {
        ans = ans.max(low[i] + high[i+1])
    }
    for i in 0..w-1 {
        ans = ans.max(left[i] + right[i+1]);
    }

    println!("{}", ans);

}