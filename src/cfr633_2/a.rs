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
        self.n += 1; self.v[self.n-1].parse().expect(&self.v[self.n-1])
    }
    #[allow(dead_code)]
    fn nexts<T>(&mut self, n: usize) -> Vec<T>
    where T: std::str::FromStr, T::Err: std::fmt::Debug {
        let mut v = Vec::with_capacity(n); for _ in 0..n { v.push(self.next()); } v
    }
}

//use std::cmp::{max, min}
fn main() {
    let mut r = Reader::new();
    let t: usize = r.next();
    for _ in 0..t {
        let n: usize = r.next();
        println!("{}", n);
    }
}
