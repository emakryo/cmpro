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
    input!{
        t: usize,
        a: [[i64]; t],
    }

    let m = 200005;
    let mut sieve = vec![false; m];
    for i in 2..m {
        if sieve[i] {
            continue;
        }
        for j in 2..m {
            if i*j >= m { break; }
            sieve[i*j] = true;
        }
    }

    for ai in a {
        solve(ai, &sieve);
    }

}

fn solve(a: Vec<i64>, sieve: &Vec<bool>) {
    let sum = a.iter().sum::<i64>();

    let mut ans = (1..=a.len()).collect::<Vec<_>>();
    if !sieve[sum as usize] {
        let mut idx = 0;
        for (i, ai) in a.into_iter().enumerate() {
            if ai % 2 == 1 {
                idx = i;
                break;
            }
        }

        ans.remove(idx);
    }

    println!("{}", ans.len());
    println!("{}", ans.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(" "));
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_shl() {
        let n = 130;
        let mut x = BitSet::new(n);
        x.set(0, true);
        x.set(1, true);
        x.set(63, true);
        x.set(64, true);
        x.set(66, true);
        x.set(127, true);
        x.set(128, true);

        let k = 1;
        let mut y = x.shl(k);

        for i in 0..n {
            if i < k {
                assert_eq!(y.get(i), false);
            } else {
                dbg!(i, y.get(i), x.get(i-k));
                assert_eq!(y.get(i), x.get(i-k));
            }
        }

        let k = 64;
        let mut y = x.shl(k);

        for i in 0..n {
            if i < k {
                assert_eq!(y.get(i), false);
            } else {
                dbg!(i, y.get(i), x.get(i-k));
                assert_eq!(y.get(i), x.get(i-k));
            }
        }

        let k = 129;
        let mut y = x.shl(k);

        for i in 0..n {
            if i < k {
                assert_eq!(y.get(i), false);
            } else {
                dbg!(i, y.get(i), x.get(i-k));
                assert_eq!(y.get(i), x.get(i-k));
            }
        }
    }

    #[test]
    fn test_shr() {
        let n = 130;
        let mut x = BitSet::new(n);
        x.set(0, true);
        x.set(1, true);
        x.set(63, true);
        x.set(64, true);
        x.set(66, true);
        x.set(127, true);
        x.set(128, true);

        let k = 1;
        let mut y = x.shr(k);

        for i in 0..n {
            if n - k <= i  {
                assert_eq!(y.get(i), false);
            } else {
                dbg!(i, y.get(i), x.get(i+k));
                assert_eq!(y.get(i), x.get(i+k));
            }
        }

        let k = 64;
        let mut y = x.shr(k);

        for i in 0..n {
            if n - k <= i {
                assert_eq!(y.get(i), false);
            } else {
                dbg!(i, y.get(i), x.get(i+k));
                assert_eq!(y.get(i), x.get(i+k));
            }
        }

        let k = 129;
        let mut y = x.shr(k);

        for i in 0..n {
            if n - k <= i {
                assert_eq!(y.get(i), false);
            } else {
                dbg!(i, y.get(i), x.get(i+k));
                assert_eq!(y.get(i), x.get(i+k));
            }
        }
    }
}

pub mod input {
    #[macro_export]
    macro_rules! input{
        (sc=$sc:expr,$($r:tt)*)=>{
            input_inner!{$sc,$($r)*}
        };
        ($($r:tt)*)=>{
            let mut sc=input::Scanner::new(std::io::stdin().lock());
            input_inner!{sc,$($r)*}
        };
    }

    #[macro_export]
    macro_rules! input_inner{
        ($sc:expr)=>{};
        ($sc:expr,)=>{};
        ($sc:expr,$var:ident:$t:tt$($r:tt)*)=>{
            let $var=read_value!($sc,$t);
            input_inner!{$sc $($r)*}
        };
    }

    #[macro_export]
    macro_rules! read_value{
        ($sc:expr,($($t:tt),*))=>{
            ($(read_value!($sc,$t)),*)
        };
        ($sc:expr,[$t:tt;$len:expr])=>{
            (0..$len).map(|_|read_value!($sc,$t)).collect::<Vec<_>>()
        };
        ($sc:expr,[$t:tt])=>{{
            let len = read_value!($sc, usize);
            (0..len).map(|_|read_value!($sc,$t)).collect::<Vec<_>>()
        }};
        ($sc:expr,Chars)=>{read_value!($sc,String).chars().collect::<Vec<char>>()};
        ($sc:expr,Usize1)=>{read_value!($sc,usize)-1};
        ($sc:expr,$t:ty)=>{$sc.next::<$t>()};
    }
    pub struct Scanner {
        s: Box<str>,
        input: std::iter::Peekable<std::str::SplitAsciiWhitespace<'static>>,
    }
    impl Scanner {
        pub fn new<R: std::io::Read>(mut reader: R) -> Self {
            let s = {
                let mut s = String::new();
                reader.read_to_string(&mut s).unwrap();
                s.into_boxed_str()
            };
            let mut sc = Scanner {
                s,
                input: "".split_ascii_whitespace().peekable(),
            };
            use std::mem;
            let s: &'static str = unsafe { mem::transmute(&*sc.s) };
            sc.input = s.split_ascii_whitespace().peekable();
            sc
        }
        #[inline]
        pub fn next<T: std::str::FromStr>(&mut self) -> T
        where
            T::Err: std::fmt::Debug,
        {
            self.input
                .next()
                .unwrap()
                .parse::<T>()
                .expect("Parse error")
        }
    }
}
