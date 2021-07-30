#![allow(unused_macros, unused_imports)]

use std::collections::HashMap;
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
        ps: [(i64, i64); n],
    }

    let qs: Vec<_> = ps.iter().map(|(x, y)| P { re: *x as f64, im: *y as f64}).collect();

    let mut online = true;
    let line = [qs[0], qs[1]];
    for i in 0..n {
        if !intersect(line, qs[i]) {
            online = false;
        }
    }

    if online {
        let mut xs: Vec<_> = ps.iter().map(|x| x.0).collect();
        xs.sort();
        xs.dedup();
        let (min_k, max_k) = if xs.len() == 1 {
            let ys: Vec<_> = ps.iter().map(|x| x.1).collect();
            let min_k = ys.iter().enumerate().map(|(x, y)| (y, x)).min().unwrap().1;
            let max_k = ys.iter().enumerate().map(|(x, y)| (y, x)).max().unwrap().1;
            (min_k, max_k)
        } else {
            let xs: Vec<_> = ps.iter().map(|x| x.0).collect();
            let min_k = xs.iter().enumerate().map(|(x, y)| (y, x)).min().unwrap().1;
            let max_k = xs.iter().enumerate().map(|(x, y)| (y, x)).max().unwrap().1;
            (min_k, max_k)

        };
        for i in 0..n {
            if i == min_k || i == max_k {
                println!("0.5");
            } else {
                println!("0");
            }
        }
        return;
    }

    let mut map = HashMap::new();
    for (i, &p) in ps.iter().enumerate() {
        map.insert(p, i);
    }
    let mut hull = convex_hull(&qs);

    if hull.first() == hull.last() {
        hull.pop();
    }

    let mut ans = vec![0.0; n];
    let m = hull.len();
    for i in 0..m {
        let a = hull[(i+m-1)%m];
        let b = hull[i];
        let c = hull[(i+1)%m];

        let a = a - b;
        let c = c - b;

        let x = (c * (-a.conj())).arg() / (2.0 * std::f64::consts::PI);
        let k = *map.get(&(b.re as i64, b.im as i64)).unwrap();
        ans[k] = x;
    }

    for a in ans {
        println!("{}", a);
    }
}

type P = num_complex::Complex64;
const EPS: f64 = 1e-8;

fn cross(a: P, b: P) -> f64 {
    (a.conj() * b).im
}
fn dot(a: P, b: P) -> f64 {
    (a.conj() * b).re
}
fn ccw(a: P, b: P, c:P) -> i32 {
    let b = b-a;
    let c = c-a;
    if cross(b, c) > 0.into() { 1 } // counter clockwise
    else if cross(b, c) < 0.into() { -1 } // clockwise
    else if dot(b, c) < 0.into() { 2 } // c -- a -- b on line
    else if b.norm() < c.norm() { -2 } // a -- b -- c on line (including a == b)
    else { 0 } // a -- c -- b on line (including b == c and a == c)
}
fn intersect(line: [P; 2], p: P) -> bool {
    cross(line[0]-p, line[1]-p).abs() < EPS
}

fn convex_hull(points: &[P]) -> Vec<P> {
    assert!(points.len() >= 3);
    let mut ps = points.to_owned();
    ps.sort_by(|a, b| if a.re != b.re {
        a.re.partial_cmp(&b.re).unwrap()
    } else {
        a.im.partial_cmp(&b.im).unwrap()
    });

    let mut hull = vec![];
    for &p in &ps {
        while hull.len() >= 2 && ccw(hull[hull.len()-2], hull[hull.len()-1], p) <= 0 {
            hull.pop();
        }
        hull.push(p);
    }
    let m = hull.len();
    for &p in ps.iter().rev().skip(1) {
        while hull.len() >= m+1 && ccw(hull[hull.len()-2], hull[hull.len()-1], p) <= 0 {
            hull.pop();
        }
        hull.push(p);
    }

    hull
}