fn read_line() -> Vec<String> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).expect("Failed to read line");
    line.trim().split_whitespace().map(|s| s.to_string()).collect()
}
struct Reader { v: Vec<String>, n: usize }
impl Reader {
    fn new() -> Self { Reader { v: read_line(), n: 0 } }
    #[allow(dead_code)]
    fn next<T>(&mut self) -> T where T: std::str::FromStr, T::Err: std::fmt::Debug {
        if self.n == self.v.len() { self.v = read_line(); self.n = 0; }
        self.n += 1; self.v[self.n-1].parse().expect("Failed to parse")
    }
    #[allow(dead_code)]
    fn nexts<T>(&mut self, n: usize) -> Vec<T>
    where T: std::str::FromStr, T::Err: std::fmt::Debug {
        (0..n).map(|_| self.next()).collect()
    }
}

struct Problem {
    r: Reader,
}

impl Problem {
    fn new() {
        let mut r = Reader::new();
        let t: usize = r.next();
        let mut s = Self { r };
        for _ in 0..t {
            s.solve();
        }
    }
    fn solve(&mut self) {
        let n: usize = self.r.next();
        let mut a : Vec<i64> = vec![];
        for _ in 0..n {
            a.push(self.r.next());
        }
        a.sort();

        let mut ans = vec![];
        for i in 0..n {
            let idx = if i%2==0 { n/2+i/2 } else { n/2-(i+1)/2 };
            ans.push(format!("{}", a[idx]));
        }
        println!("{}", ans.join(" "));
    }
}


//use std::cmp::{max, min}
fn main() {
    Problem::new();
}
