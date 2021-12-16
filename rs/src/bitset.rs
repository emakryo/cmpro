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