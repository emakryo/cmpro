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
    let mut r = Reader::new();
    let h = r.next();
    let w = r.next();
    let mut a: Vec<Vec<i64>> = Vec::new();
    let mut b: Vec<Vec<i64>> = Vec::new();
    for _ in 0..h {
        a.push(r.nexts(w));
    }
    for _ in 0..h {
        b.push(r.nexts(w));
    }

    let mut dp = Vec::new();
    for i in 0..(h+1) {
        dp.push(vec![]);
        for _ in 0..(w+1) {
            dp[i].push(vec![false; 12800]);
        }
    }
    let x = (a[0][0]-b[0][0]).abs() as usize;
    dp[1][1][x] = true;;

    for i in 0..h {
        for j in 0..w {
            for k in 0..12800 {
                let d = (a[i][j]-b[i][j]).abs();
                let k1 = (k as i64 - d).abs() as usize;
                let k2 = k + d as usize;
                if k2 >= 12800 {
                    continue;
                }
                dp[i+1][j+1][k] = dp[i+1][j+1][k] || dp[i][j+1][k1] || dp[i][j+1][k2];
                dp[i+1][j+1][k] = dp[i+1][j+1][k] || dp[i+1][j][k1] || dp[i+1][j][k2];
            }
        }
    }
    for k in 0..12800 {
        if dp[h][w][k] {
            println!("{}", k);
            return;
        }
    }
}
