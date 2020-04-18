#![allow(unknown_lints, dead_code, unused_imports, unused_macros)]
use std::cmp::{max, min};
#[cfg(not(DBG))]
macro_rules! debug { ($($xs:expr),*) => () }
#[cfg(DBG)]
macro_rules! debug { ($($xs:expr),*) => { println!("{:?}", ($($xs),*))} }

fn read_line() -> Vec<String> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).expect("Failed to read line");
    line.trim().split_whitespace().map(|s| s.to_string()).collect()
}
struct Reader { v: Vec<String>, n: usize }
impl Reader {
    fn new() -> Self { Reader { v: read_line(), n: 0 } }
    fn next<T: std::str::FromStr>(&mut self) -> T {
        if self.n == self.v.len() { self.v = read_line(); self.n = 0; }
        self.n += 1; self.v[self.n-1].parse().ok().unwrap()
    }
    fn nexts<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        (0..n).map(|_| self.next()).collect()
    }
}

fn gcd(x: u64, y: u64) -> u64 {
    if y == 0 { x } else { gcd(y, x%y) }
}

fn main() {
    let mut r = Reader::new();
    let n: i64 = r.next();
    let x: i64 = r.next();
    let d: i64 = r.next();

    if d == 0 {
        if x == 0 {
            println!("{}", 1);
        } else {
            println!("{}", n+1);
        }
        return;
    }

    let g = gcd(x.abs() as u64, d.abs() as u64);

    let x = x / g as i64 * d.signum();
    let d = d / g as i64 * d.signum();

    let mut left = vec![];
    let mut right = vec![];
    for m in 0..(n+1) {
        let k = (m - m%d) / d;
        left.push(m * (m-1) / 2 + k*x);
        right.push(m * (2*n as i64-m-1) / 2 + k*x + 1);
    }

    let mut ans = 0;
    for k in 0..min(n+1, d) {
        let mut vs = vec![];
        for i in (0..).map(|i| k + i * d).take_while(|&i| i <= n) {
            vs.push((left[i as usize], i));
            vs.push((right[i as usize], i+n+1));
        }

        vs.sort();

        let mut start = 1e18 as i64;
        let mut level = 0;
        for &(x, j) in vs.iter() {
            if j < n+1 {
                start = min(start, x);
                level += 1;
            } else {
                level -= 1;
                if level == 0 {
                    ans += x - start;
                    start = 1e18 as i64;
                }
            }
            //debug!(x, j, start, level, ans);
        }
    }

    println!("{}", ans);
}
