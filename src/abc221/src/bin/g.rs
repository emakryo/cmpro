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
        n: usize,
        a: i64,
        b: i64,
        d: [usize; n],
    }

    let s = d.iter().map(|x| *x as i64).sum::<i64>();

    if !(0..=2*s).contains(&(s - a - b)) || (s - a - b) % 2 == 1 || !(0..=2*s).contains(&(s - a + b)) || (s - a + b) % 2 == 1 {
        println!("No");
        return;
    }

    let p = (s - a - b) / 2;
    let q = (s - a + b) / 2;

    let mut dp = vec![BitSet::new(3600001); n+1];

    dp[0].set(0, true);

    for i in 0..n {
        dp[i+1] = dp[i].shl(d[i] as usize).or(&dp[i]);
    }

    if !dp[n].get(p as usize) || !dp[n].get(q as usize) {
        println!("No");
        return;
    }

    let mut xa = vec![0; n];
    let mut k = p as usize;
    for i in (0..n).rev() {
        if k >= d[i] && dp[i].get(k-d[i]) {
            k -= d[i];
            xa[i] = 1;
        }
    }

    let mut ya = vec![0; n];
    let mut k = q as usize;
    for i in (0..n).rev() {
        if k >= d[i] && dp[i].get(k-d[i]) {
            k -= d[i];
            ya[i] = 1;
        }
    }

    let mut ans = String::new();
    for i in 0..n {
        ans.push(match (xa[i], ya[i]) {
            (0, 0) => 'R',
            (0, 1) => 'U',
            (1, 0) => 'D',
            (1, 1) => 'L',
            _ => panic!(),
        })
    }

    println!("Yes\n{}", ans);
}


#[derive(Debug, Clone)]
pub struct BitSet {
    len: usize,
    bits: Vec<u64>,
}

impl BitSet {
    pub fn new(len: usize) -> Self {
        Self {
            len,
            bits: vec![0; (len+63)/64],
        }
    }
    
    pub fn get(&mut self, idx: usize) -> bool {
        assert!(idx < self.len);
        let (i0, i1) = (idx / 64, idx % 64);
        self.bits[i0] >> i1 & 1 == 1
    }

    pub fn set(&mut self, idx: usize, val: bool) {
        assert!(idx < self.len);
        let (i0, i1) = (idx / 64, idx % 64);
        if val {
            self.bits[i0] = self.bits[i0] | (1<<i1);
        } else {
            self.bits[i0] = self.bits[i0] & !(1<<i1);
        }
    }

    pub fn clear(&mut self) {
        self.bits.clear();
        self.bits.resize((self.len+63)/64, 0);
    }

    /// s << k,
    /// i.e. (s << k)[i] = s[i-k]  (k <= i)
    ///      (s << k)[i] = 0 (i < k)
    pub fn shl(&self, k: usize) -> Self {
        let (k0, k1) = (k / 64, k % 64);
        let n = self.bits.len();
        let mut ret = vec![0; n];
        for i in 0..n {
            if i + k0 >= n { break }
            ret[i+k0] = self.bits[i] << k1;
        }

        if k1 > 0 {
            for i in 0..n {
                if i + k0 + 1 >= n { break }
                ret[i+k0+1] |= self.bits[i] >> (64-k1);
            }
        }

        Self {
            len: self.len,
            bits: ret,
        }
    }

    /// s >> k
    /// i.e. (s >> k)[i] = s[i+k] (k < n-i)
    /// i.e. (s >> k)[i] = 0 (n-i <= k)
    pub fn shr(&self, k: usize) -> Self {
        let (k0, k1) = (k / 64, k % 64);
        let n = self.bits.len();
        let mut ret = vec![0; n];

        for i in k0..n {
            ret[i-k0] = self.bits[i] >> k1;
        }

        if k1 > 0 {
            for i in k0+1..n {
                ret[i-k0-1] |= self.bits[i] << (64 - k1);
            }
        }

        Self {
            len: self.len,
            bits: ret,
        }
    }

    pub fn or(mut self, other: &Self) -> Self {
        let n = self.bits.len();
        for i in 0..n {
            self.bits[i] |= other.bits[i];
        }

        self
    }

    pub fn and(mut self, other: &Self) -> Self {
        let n = self.bits.len();
        for i in 0..n {
            self.bits[i] &= other.bits[i];
        }

        self
    }
}
