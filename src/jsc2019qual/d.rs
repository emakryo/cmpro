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

fn dfs(cnt: usize, low: usize, high: usize, ans: &mut Vec<Vec<usize>>) {
    let med = (low + high) / 2;
    for i in low..med {
        for j in med..high {
            ans[i][j] = cnt;
            ans[j][i] = cnt;
        }
    }

    if med - low > 1 {
        dfs(cnt+1, low, med, ans);
    }
    if high - med > 1 {
        dfs(cnt+1, med, high, ans);
    }
}

fn main() {
    let mut r = Reader::new();
    let n: usize = r.next();

    let mut ans: Vec<Vec<usize>> = (0..n).map(|_| vec![0; n]).collect();

    dfs(1, 0, n, &mut ans);

    for i in 0..(n-1) {
        for j in (i+1)..n {
            if j == n-1 {
                println!("{}", ans[i][j]);
            } else {
                print!("{} ", ans[i][j]);
            }
        }
    }
}
