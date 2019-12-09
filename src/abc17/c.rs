use std::io::Write;

macro_rules! eprintln {
    ($($args:tt)*) => { let _ = writeln!(&mut std::io::stderr(), $($args)*); }
}

fn read_line() -> Vec<String> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).expect("Failed to read line");
    line.trim().split_whitespace().map(|s| s.to_string()).collect()
}

struct Reader { v: Vec<String>, n: usize }

impl Reader {
    fn new() -> Self { Reader { v: read_line(), n: 0 } }
    fn next<T>(&mut self) -> T where T: std::str::FromStr, T::Err: std::fmt::Debug {
        if self.n == self.v.len() { self.v = read_line(); self.n = 0; }
        self.n += 1;
        self.v[self.n-1].parse().expect(&self.v[self.n-1])
    }
    #[allow(dead_code)]
    fn nexts<T>(&mut self, n: usize) -> Vec<T>
    where T: std::str::FromStr, T::Err: std::fmt::Debug {
        let mut v = Vec::with_capacity(n);
        for _ in 0..n { v.push(self.next()); }
        v
    }
}

fn main() {
    let mut rd = Reader::new();
    let n: usize = rd.next();
    let m: usize = rd.next();
    let mut l: Vec<usize> = vec![0; n];
    let mut r: Vec<usize> = vec![0; n];
    let mut s: Vec<usize> = vec![0; n];
    for i in 0..n {
        l[i] = rd.next::<usize>()-1;
        r[i] = rd.next::<usize>()-1;
        s[i] = rd.next();
    }

    let total: usize = s.iter().sum();
    let mut li: Vec<_> = l.iter().enumerate().map(|(i, &x)| (x, i)).collect();
    let mut ri: Vec<_> = r.iter().enumerate().map(|(i, &x)| (x, i)).collect();
    li.sort();
    ri.sort();

    let mut a = vec![0; m];
    let mut b = vec![0; m];
    for i in 0..n {
        a[l[i]] += s[i];
        b[r[i]] += s[i];
    }

    let mut sum = 0;
    let mut ans = 0;
    for i in 0..m {
        sum += a[i];
        if total - sum > ans {
            ans = total - sum;
        }
        sum -= b[i];
    }
    println!("{}", ans);
}
