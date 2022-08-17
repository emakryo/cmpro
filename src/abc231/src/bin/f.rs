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
        a: [i64; n],
        b: [i64; n],
    }

    let mut vb = b.clone();
    vb.sort();
    vb.dedup();
    let b = b.iter().map(|bi| vb.binary_search(bi).unwrap()).collect::<Vec<usize>>();

    let mut xs = BTreeMap::<i64, Vec<usize>>::new();
    for (&ai, &bi) in a.iter().zip(b.iter()) {
        xs.entry(ai).or_default().push(bi);
    }

    let mut ans = 0i64;
    let mut bit = FenwickTree::new(n, 0);
    for (_, bs) in xs {
        for &bi in &bs {
            bit.add(bi, 1);
        }

        for &bi in &bs {
            ans += bit.sum(bi, n);
        }
    }

    println!("{}", ans);
}

pub mod combination {
    use crate::modint::ModIntBase;

    #[derive(Debug)]
    pub struct Combination<M> {
        fact: Vec<M>,
        fact_inv: Vec<M>,
    }

    impl<M: ModIntBase> Combination<M> {
        pub fn new(n_max: usize) -> Self {
            let n = n_max.min(M::modulus() as usize);
            let mut fact = vec![M::from(1); n];
            let mut fact_inv = vec![M::from(1); n];
            for i in 2..n {
                fact[i] = fact[i - 1] * i.into();
                fact_inv[i] = fact[i].inv();
            }

            Self { fact, fact_inv }
        }

        pub fn calc(&self, n: usize, k: usize) -> M {
            if n < k {
                0.into()
            } else if n < self.fact.len() {
                self.fact[n] * self.fact_inv[k] * self.fact_inv[n - k]
            } else {
                self.comb_ext(n, k)
            }
        }

        fn fact_ext(&self, n: usize, e: &mut usize) -> M {
            if n == 0 {
                *e = 0;
                return 1.into();
            }

            let m = self.fact.len();
            let na = self.fact_ext(n / m, e);
            *e += n / m;
            let mut a = na * self.fact[n % m];
            if n / m % 2 == 1 {
                a *= (m - 1).into();
            }
            a
        }

        fn comb_ext(&self, n: usize, k: usize) -> M {
            let (mut e1, mut e2, mut e3) = (0, 0, 0);
            let (a1, a2, a3) = (
                self.fact_ext(n, &mut e1),
                self.fact_ext(k, &mut e2),
                self.fact_ext(n - k, &mut e3),
            );
            if e1 > e2 + e3 {
                0.into()
            } else {
                a1 * (a2 * a3).inv()
            }
        }
    }
}
pub mod convolution {
    macro_rules! modulus {
    ($($name:ident),*) => {
        $(
            #[derive(Copy, Clone, Eq, PartialEq)]
            enum $name {}

            impl Modulus for $name {
                const VALUE: u32 = $name as _;
                const HINT_VALUE_IS_PRIME: bool = true;

                fn butterfly_cache() -> &'static ::std::thread::LocalKey<::std::cell::RefCell<::std::option::Option<crate::modint::ButterflyCache<Self>>>> {
                    thread_local! {
                        static BUTTERFLY_CACHE: ::std::cell::RefCell<::std::option::Option<crate::modint::ButterflyCache<$name>>> = ::std::default::Default::default();
                    }
                    &BUTTERFLY_CACHE
                }
            }
        )*
    };
}

    use crate::{
        internal_bit, internal_math,
        modint::{ButterflyCache, Modulus, RemEuclidU32, StaticModInt},
    };
    use std::{
        cmp,
        convert::{TryFrom, TryInto as _},
        fmt,
    };

    #[allow(clippy::many_single_char_names)]
    pub fn convolution<M>(a: &[StaticModInt<M>], b: &[StaticModInt<M>]) -> Vec<StaticModInt<M>>
    where
        M: Modulus,
    {
        if a.is_empty() || b.is_empty() {
            return vec![];
        }
        let (n, m) = (a.len(), b.len());

        if cmp::min(n, m) <= 60 {
            let (n, m, a, b) = if n < m { (m, n, b, a) } else { (n, m, a, b) };
            let mut ans = vec![StaticModInt::new(0); n + m - 1];
            for i in 0..n {
                for j in 0..m {
                    ans[i + j] += a[i] * b[j];
                }
            }
            return ans;
        }

        let (mut a, mut b) = (a.to_owned(), b.to_owned());
        let z = 1 << internal_bit::ceil_pow2((n + m - 1) as _);
        a.resize(z, StaticModInt::raw(0));
        butterfly(&mut a);
        b.resize(z, StaticModInt::raw(0));
        butterfly(&mut b);
        for (a, b) in a.iter_mut().zip(&b) {
            *a *= b;
        }
        butterfly_inv(&mut a);
        a.resize(n + m - 1, StaticModInt::raw(0));
        let iz = StaticModInt::new(z).inv();
        for a in &mut a {
            *a *= iz;
        }
        a
    }

    pub fn convolution_raw<T, M>(a: &[T], b: &[T]) -> Vec<T>
    where
        T: RemEuclidU32 + TryFrom<u32> + Clone,
        T::Error: fmt::Debug,
        M: Modulus,
    {
        let a = a.iter().cloned().map(Into::into).collect::<Vec<_>>();
        let b = b.iter().cloned().map(Into::into).collect::<Vec<_>>();
        convolution::<M>(&a, &b)
            .into_iter()
            .map(|z| {
                z.val()
                    .try_into()
                    .expect("the numeric type is smaller than the modulus")
            })
            .collect()
    }

    #[allow(clippy::many_single_char_names)]
    pub fn convolution_i64(a: &[i64], b: &[i64]) -> Vec<i64> {
        const M1: u64 = 754_974_721; // 2^24
        const M2: u64 = 167_772_161; // 2^25
        const M3: u64 = 469_762_049; // 2^26
        const M2M3: u64 = M2 * M3;
        const M1M3: u64 = M1 * M3;
        const M1M2: u64 = M1 * M2;
        const M1M2M3: u64 = M1M2.wrapping_mul(M3);

        modulus!(M1, M2, M3);

        if a.is_empty() || b.is_empty() {
            return vec![];
        }

        let (_, i1) = internal_math::inv_gcd(M2M3 as _, M1 as _);
        let (_, i2) = internal_math::inv_gcd(M1M3 as _, M2 as _);
        let (_, i3) = internal_math::inv_gcd(M1M2 as _, M3 as _);

        let c1 = convolution_raw::<i64, M1>(a, b);
        let c2 = convolution_raw::<i64, M2>(a, b);
        let c3 = convolution_raw::<i64, M3>(a, b);

        c1.into_iter()
            .zip(c2)
            .zip(c3)
            .map(|((c1, c2), c3)| {
                const OFFSET: &[u64] = &[0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3];

                let mut x = [(c1, i1, M1, M2M3), (c2, i2, M2, M1M3), (c3, i3, M3, M1M2)]
                    .iter()
                    .map(|&(c, i, m1, m2)| {
                        c.wrapping_mul(i).rem_euclid(m1 as _).wrapping_mul(m2 as _)
                    })
                    .fold(0, i64::wrapping_add);

                // B = 2^63, -B <= x, r(real value) < B
                // (x, x - M, x - 2M, or x - 3M) = r (mod 2B)
                // r = c1[i] (mod MOD1)
                // focus on MOD1
                // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64) (mod 2B)
                // r = x,
                //     x - M' + (0 or 2B),
                //     x - 2M' + (0, 2B or 4B),
                //     x - 3M' + (0, 2B, 4B or 6B) (without mod!)
                // (r - x) = 0, (0)
                //           - M' + (0 or 2B), (1)
                //           -2M' + (0 or 2B or 4B), (2)
                //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)
                // we checked that
                //   ((1) mod MOD1) mod 5 = 2
                //   ((2) mod MOD1) mod 5 = 3
                //   ((3) mod MOD1) mod 5 = 4
                let mut diff = c1 - internal_math::safe_mod(x, M1 as _);
                if diff < 0 {
                    diff += M1 as i64;
                }
                x = x.wrapping_sub(OFFSET[diff.rem_euclid(5) as usize] as _);
                x
            })
            .collect()
    }

    #[allow(clippy::many_single_char_names)]
    fn butterfly<M: Modulus>(a: &mut [StaticModInt<M>]) {
        let n = a.len();
        let h = internal_bit::ceil_pow2(n as u32);

        M::butterfly_cache().with(|cache| {
            let mut cache = cache.borrow_mut();
            let ButterflyCache { sum_e, .. } = cache.get_or_insert_with(prepare);
            for ph in 1..=h {
                let w = 1 << (ph - 1);
                let p = 1 << (h - ph);
                let mut now = StaticModInt::<M>::new(1);
                for s in 0..w {
                    let offset = s << (h - ph + 1);
                    for i in 0..p {
                        let l = a[i + offset];
                        let r = a[i + offset + p] * now;
                        a[i + offset] = l + r;
                        a[i + offset + p] = l - r;
                    }
                    now *= sum_e[(!s).trailing_zeros() as usize];
                }
            }
        });
    }

    #[allow(clippy::many_single_char_names)]
    fn butterfly_inv<M: Modulus>(a: &mut [StaticModInt<M>]) {
        let n = a.len();
        let h = internal_bit::ceil_pow2(n as u32);

        M::butterfly_cache().with(|cache| {
            let mut cache = cache.borrow_mut();
            let ButterflyCache { sum_ie, .. } = cache.get_or_insert_with(prepare);
            for ph in (1..=h).rev() {
                let w = 1 << (ph - 1);
                let p = 1 << (h - ph);
                let mut inow = StaticModInt::<M>::new(1);
                for s in 0..w {
                    let offset = s << (h - ph + 1);
                    for i in 0..p {
                        let l = a[i + offset];
                        let r = a[i + offset + p];
                        a[i + offset] = l + r;
                        a[i + offset + p] = StaticModInt::new(M::VALUE + l.val() - r.val()) * inow;
                    }
                    inow *= sum_ie[(!s).trailing_zeros() as usize];
                }
            }
        });
    }

    fn prepare<M: Modulus>() -> ButterflyCache<M> {
        let g = StaticModInt::<M>::raw(internal_math::primitive_root(M::VALUE as i32) as u32);
        let mut es = [StaticModInt::<M>::raw(0); 30]; // es[i]^(2^(2+i)) == 1
        let mut ies = [StaticModInt::<M>::raw(0); 30];
        let cnt2 = (M::VALUE - 1).trailing_zeros() as usize;
        let mut e = g.pow(((M::VALUE - 1) >> cnt2).into());
        let mut ie = e.inv();
        for i in (2..=cnt2).rev() {
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        let sum_e = es
            .iter()
            .scan(StaticModInt::new(1), |acc, e| {
                *acc *= e;
                Some(*acc)
            })
            .collect();
        let sum_ie = ies
            .iter()
            .scan(StaticModInt::new(1), |acc, ie| {
                *acc *= ie;
                Some(*acc)
            })
            .collect();
        ButterflyCache { sum_e, sum_ie }
    }
}
pub mod dsu {
    /// Implement (union by size) + (path compression)
    /// Reference:
    /// Zvi Galil and Giuseppe F. Italiano,
    /// Data structures and algorithms for disjoint set union problems
    pub struct Dsu {
        n: usize,
        // root node: -1 * component size
        // otherwise: parent
        parent_or_size: Vec<i32>,
    }

    impl Dsu {
        // 0 <= size <= 10^8 is constrained.
        pub fn new(size: usize) -> Self {
            Self {
                n: size,
                parent_or_size: vec![-1; size],
            }
        }
        pub fn merge(&mut self, a: usize, b: usize) -> usize {
            assert!(a < self.n);
            assert!(b < self.n);
            let (mut x, mut y) = (self.leader(a), self.leader(b));
            if x == y {
                return x;
            }
            if -self.parent_or_size[x] < -self.parent_or_size[y] {
                std::mem::swap(&mut x, &mut y);
            }
            self.parent_or_size[x] += self.parent_or_size[y];
            self.parent_or_size[y] = x as i32;
            x
        }

        pub fn same(&mut self, a: usize, b: usize) -> bool {
            assert!(a < self.n);
            assert!(b < self.n);
            self.leader(a) == self.leader(b)
        }
        pub fn leader(&mut self, a: usize) -> usize {
            assert!(a < self.n);
            if self.parent_or_size[a] < 0 {
                return a;
            }
            self.parent_or_size[a] = self.leader(self.parent_or_size[a] as usize) as i32;
            self.parent_or_size[a] as usize
        }
        pub fn size(&mut self, a: usize) -> usize {
            assert!(a < self.n);
            let x = self.leader(a);
            -self.parent_or_size[x] as usize
        }
        pub fn groups(&mut self) -> Vec<Vec<usize>> {
            let mut leader_buf = vec![0; self.n];
            let mut group_size = vec![0; self.n];
            for i in 0..self.n {
                leader_buf[i] = self.leader(i);
                group_size[leader_buf[i]] += 1;
            }
            let mut result = vec![Vec::new(); self.n];
            for i in 0..self.n {
                result[i].reserve(group_size[i]);
            }
            for i in 0..self.n {
                result[leader_buf[i]].push(i);
            }
            result
                .into_iter()
                .filter(|x| !x.is_empty())
                .collect::<Vec<Vec<usize>>>()
        }
    }
}
pub mod fenwicktree {
    // Reference: https://en.wikipedia.org/wiki/Fenwick_tree
    pub struct FenwickTree<T> {
        n: usize,
        ary: Vec<T>,
        e: T,
    }

    impl<T: Clone + std::ops::AddAssign<T>> FenwickTree<T> {
        pub fn new(n: usize, e: T) -> Self {
            FenwickTree {
                n,
                ary: vec![e.clone(); n],
                e,
            }
        }
        pub fn accum(&self, mut idx: usize) -> T {
            let mut sum = self.e.clone();
            while idx > 0 {
                sum += self.ary[idx - 1].clone();
                idx &= idx - 1;
            }
            sum
        }
        /// performs data[idx] += val;
        pub fn add<U: Clone>(&mut self, mut idx: usize, val: U)
        where
            T: std::ops::AddAssign<U>,
        {
            let n = self.n;
            idx += 1;
            while idx <= n {
                self.ary[idx - 1] += val.clone();
                idx += idx & idx.wrapping_neg();
            }
        }
        /// Returns data[l] + ... + data[r - 1].
        pub fn sum(&self, l: usize, r: usize) -> T
        where
            T: std::ops::Sub<Output = T>,
        {
            self.accum(r) - self.accum(l)
        }
    }
}
pub mod internal_bit {
    // Skipped:
    //
    // - `bsf` = `__builtin_ctz`: is equivalent to `{integer}::trailing_zeros`

    #[allow(dead_code)]
    pub(crate) fn ceil_pow2(n: u32) -> u32 {
        32 - n.saturating_sub(1).leading_zeros()
    }
}
pub mod internal_math {
    // remove this after dependencies has been added
    #![allow(dead_code)]
    use std::mem::swap;

    /// # Arguments
    /// * `m` `1 <= m`
    ///
    /// # Returns
    /// x mod m
    /* const */
    pub(crate) fn safe_mod(mut x: i64, m: i64) -> i64 {
        x %= m;
        if x < 0 {
            x += m;
        }
        x
    }

    /// Fast modular by barrett reduction
    /// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
    /// NOTE: reconsider after Ice Lake
    pub(crate) struct Barrett {
        pub(crate) _m: u32,
        pub(crate) im: u64,
    }

    impl Barrett {
        /// # Arguments
        /// * `m` `1 <= m`
        /// (Note: `m <= 2^31` should also hold, which is undocumented in the original library.
        /// See the [pull reqeust commment](https://github.com/rust-lang-ja/ac-library-rs/pull/3#discussion_r484661007)
        /// for more details.)
        pub(crate) fn new(m: u32) -> Barrett {
            Barrett {
                _m: m,
                im: (-1i64 as u64 / m as u64).wrapping_add(1),
            }
        }

        /// # Returns
        /// `m`
        pub(crate) fn umod(&self) -> u32 {
            self._m
        }

        /// # Parameters
        /// * `a` `0 <= a < m`
        /// * `b` `0 <= b < m`
        ///
        /// # Returns
        /// a * b % m
        #[allow(clippy::many_single_char_names)]
        pub(crate) fn mul(&self, a: u32, b: u32) -> u32 {
            mul_mod(a, b, self._m, self.im)
        }
    }

    /// Calculates `a * b % m`.
    ///
    /// * `a` `0 <= a < m`
    /// * `b` `0 <= b < m`
    /// * `m` `1 <= m <= 2^31`
    /// * `im` = ceil(2^64 / `m`)
    #[allow(clippy::many_single_char_names)]
    pub(crate) fn mul_mod(a: u32, b: u32, m: u32, im: u64) -> u32 {
        // [1] m = 1
        // a = b = im = 0, so okay

        // [2] m >= 2
        // im = ceil(2^64 / m)
        // -> im * m = 2^64 + r (0 <= r < m)
        // let z = a*b = c*m + d (0 <= c, d < m)
        // a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im
        // c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) < 2^64 * 2
        // ((ab * im) >> 64) == c or c + 1
        let mut z = a as u64;
        z *= b as u64;
        let x = (((z as u128) * (im as u128)) >> 64) as u64;
        let mut v = z.wrapping_sub(x.wrapping_mul(m as u64)) as u32;
        if m <= v {
            v = v.wrapping_add(m);
        }
        v
    }

    /// # Parameters
    /// * `n` `0 <= n`
    /// * `m` `1 <= m`
    ///
    /// # Returns
    /// `(x ** n) % m`
    /* const */
    #[allow(clippy::many_single_char_names)]
    pub(crate) fn pow_mod(x: i64, mut n: i64, m: i32) -> i64 {
        if m == 1 {
            return 0;
        }
        let _m = m as u32;
        let mut r: u64 = 1;
        let mut y: u64 = safe_mod(x, m as i64) as u64;
        while n != 0 {
            if (n & 1) > 0 {
                r = (r * y) % (_m as u64);
            }
            y = (y * y) % (_m as u64);
            n >>= 1;
        }
        r as i64
    }

    /// Reference:
    /// M. Forisek and J. Jancina,
    /// Fast Primality Testing for Integers That Fit into a Machine Word
    ///
    /// # Parameters
    /// * `n` `0 <= n`
    /* const */
    pub(crate) fn is_prime(n: i32) -> bool {
        let n = n as i64;
        match n {
            _ if n <= 1 => return false,
            2 | 7 | 61 => return true,
            _ if n % 2 == 0 => return false,
            _ => {}
        }
        let mut d = n - 1;
        while d % 2 == 0 {
            d /= 2;
        }
        for &a in &[2, 7, 61] {
            let mut t = d;
            let mut y = pow_mod(a, t, n as i32);
            while t != n - 1 && y != 1 && y != n - 1 {
                y = y * y % n;
                t <<= 1;
            }
            if y != n - 1 && t % 2 == 0 {
                return false;
            }
        }
        true
    }

    // omitted
    // template <int n> constexpr bool is_prime = is_prime_constexpr(n);

    /// # Parameters
    /// * `b` `1 <= b`
    ///
    /// # Returns
    /// (g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
    /* const */
    #[allow(clippy::many_single_char_names)]
    pub(crate) fn inv_gcd(a: i64, b: i64) -> (i64, i64) {
        let a = safe_mod(a, b);
        if a == 0 {
            return (b, 0);
        }

        // Contracts:
        // [1] s - m0 * a = 0 (mod b)
        // [2] t - m1 * a = 0 (mod b)
        // [3] s * |m1| + t * |m0| <= b
        let mut s = b;
        let mut t = a;
        let mut m0 = 0;
        let mut m1 = 1;

        while t != 0 {
            let u = s / t;
            s -= t * u;
            m0 -= m1 * u; // |m1 * u| <= |m1| * s <= b

            // [3]:
            // (s - t * u) * |m1| + t * |m0 - m1 * u|
            // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
            // = s * |m1| + t * |m0| <= b

            swap(&mut s, &mut t);
            swap(&mut m0, &mut m1);
        }
        // by [3]: |m0| <= b/g
        // by g != b: |m0| < b/g
        if m0 < 0 {
            m0 += b / s;
        }
        (s, m0)
    }

    /// Compile time (currently not) primitive root
    /// @param m must be prime
    /// @return primitive root (and minimum in now)
    /* const */
    pub(crate) fn primitive_root(m: i32) -> i32 {
        match m {
            2 => return 1,
            167_772_161 => return 3,
            469_762_049 => return 3,
            754_974_721 => return 11,
            998_244_353 => return 3,
            _ => {}
        }

        let mut divs = [0; 20];
        divs[0] = 2;
        let mut cnt = 1;
        let mut x = (m - 1) / 2;
        while x % 2 == 0 {
            x /= 2;
        }
        for i in (3..std::i32::MAX).step_by(2) {
            if i as i64 * i as i64 > x as i64 {
                break;
            }
            if x % i == 0 {
                divs[cnt] = i;
                cnt += 1;
                while x % i == 0 {
                    x /= i;
                }
            }
        }
        if x > 1 {
            divs[cnt] = x;
            cnt += 1;
        }
        let mut g = 2;
        loop {
            if (0..cnt).all(|i| pow_mod(g, ((m - 1) / divs[i]) as i64, m) != 1) {
                break g as i32;
            }
            g += 1;
        }
    }
    // omitted
    // template <int m> constexpr int primitive_root = primitive_root_constexpr(m);
}
pub mod internal_queue {
    #![allow(dead_code)]

    #[derive(Default)]
    pub(crate) struct SimpleQueue<T> {
        payload: Vec<T>,
        pos: usize,
    }

    impl<T> SimpleQueue<T> {
        pub(crate) fn reserve(&mut self, n: usize) {
            if n > self.payload.len() {
                self.payload.reserve(n - self.payload.len());
            }
        }

        pub(crate) fn size(&self) -> usize {
            self.payload.len() - self.pos
        }

        pub(crate) fn empty(&self) -> bool {
            self.pos == self.payload.len()
        }

        pub(crate) fn push(&mut self, t: T) {
            self.payload.push(t);
        }

        // Do we need mutable version?
        pub(crate) fn front(&self) -> Option<&T> {
            if self.pos < self.payload.len() {
                Some(&self.payload[self.pos])
            } else {
                None
            }
        }

        pub(crate) fn clear(&mut self) {
            self.payload.clear();
            self.pos = 0;
        }

        pub(crate) fn pop(&mut self) -> Option<&T> {
            if self.pos < self.payload.len() {
                self.pos += 1;
                Some(&self.payload[self.pos - 1])
            } else {
                None
            }
        }
    }
}
pub mod internal_scc {
    pub struct Csr<E> {
        start: Vec<usize>,
        elist: Vec<E>,
    }

    impl<E> Csr<E>
    where
        E: Copy,
    {
        pub fn new(n: usize, edges: &[(usize, E)], init: E) -> Self {
            let mut csr = Csr {
                start: vec![0; n + 1],
                elist: vec![init; edges.len()],
            };
            for e in edges.iter() {
                csr.start[e.0 + 1] += 1;
            }
            for i in 1..=n {
                csr.start[i] += csr.start[i - 1];
            }
            let mut counter = csr.start.clone();
            for e in edges.iter() {
                csr.elist[counter[e.0]] = e.1;
                counter[e.0] += 1;
            }
            csr
        }
    }

    #[derive(Copy, Clone)]
    struct _Edge {
        to: usize,
    }

    /// Reference:
    /// R. Tarjan,
    /// Depth-First Search and Linear Graph Algorithms
    pub struct SccGraph {
        n: usize,
        edges: Vec<(usize, _Edge)>,
    }

    impl SccGraph {
        pub fn new(n: usize) -> Self {
            SccGraph { n, edges: vec![] }
        }

        pub fn num_vertices(&self) -> usize {
            self.n
        }

        pub fn add_edge(&mut self, from: usize, to: usize) {
            self.edges.push((from, _Edge { to }));
        }

        /// return pair of (# of scc, scc id)
        pub fn scc_ids(&self) -> (usize, Vec<usize>) {
            // In C++ ac-library, this function is implemented by using recursive lambda functions.
            // Instead, we use fn and struct for capturing environments.
            struct _Env {
                g: Csr<_Edge>,
                now_ord: usize,
                group_num: usize,
                visited: Vec<usize>,
                low: Vec<usize>,
                ord: Vec<Option<usize>>,
                ids: Vec<usize>,
            }
            let mut env = _Env {
                g: Csr::new(self.n, &self.edges, _Edge { to: 0 }),
                now_ord: 0,
                group_num: 0,
                visited: Vec::with_capacity(self.n),
                low: vec![0; self.n],
                ord: vec![None; self.n],
                ids: vec![0; self.n],
            };

            fn dfs(v: usize, n: usize, env: &mut _Env) {
                env.low[v] = env.now_ord;
                env.ord[v] = Some(env.now_ord);
                env.now_ord += 1;
                env.visited.push(v);

                for i in env.g.start[v]..env.g.start[v + 1] {
                    let to = env.g.elist[i].to;
                    if let Some(x) = env.ord[to] {
                        env.low[v] = std::cmp::min(env.low[v], x);
                    } else {
                        dfs(to, n, env);
                        env.low[v] = std::cmp::min(env.low[v], env.low[to]);
                    }
                }
                if env.low[v] == env.ord[v].unwrap() {
                    loop {
                        let u = *env.visited.last().unwrap();
                        env.visited.pop();
                        env.ord[u] = Some(n);
                        env.ids[u] = env.group_num;
                        if u == v {
                            break;
                        }
                    }
                    env.group_num += 1;
                }
            }
            for i in 0..self.n {
                if env.ord[i].is_none() {
                    dfs(i, self.n, &mut env);
                }
            }
            for x in env.ids.iter_mut() {
                *x = env.group_num - 1 - *x;
            }
            (env.group_num, env.ids)
        }

        pub fn scc(&self) -> Vec<Vec<usize>> {
            let ids = self.scc_ids();
            let group_num = ids.0;
            let mut counts = vec![0usize; group_num];
            for &x in ids.1.iter() {
                counts[x] += 1;
            }
            let mut groups: Vec<Vec<usize>> = (0..ids.0).map(|_| vec![]).collect();
            for i in 0..group_num {
                groups[i].reserve(counts[i]);
            }
            for i in 0..self.n {
                groups[ids.1[i]].push(i);
            }
            groups
        }
    }
}
pub mod internal_type_traits {
    use std::{
        fmt,
        iter::{Product, Sum},
        ops::{
            Add, AddAssign, BitAnd, BitAndAssign, BitOr, BitOrAssign, BitXor, BitXorAssign, Div,
            DivAssign, Mul, MulAssign, Not, Rem, RemAssign, Shl, ShlAssign, Shr, ShrAssign, Sub,
            SubAssign,
        },
    };

    // Skipped:
    //
    // - `is_signed_int_t<T>`   (probably won't be used directly in `modint.rs`)
    // - `is_unsigned_int_t<T>` (probably won't be used directly in `modint.rs`)
    // - `to_unsigned_t<T>`     (not used in `fenwicktree.rs`)

    /// Corresponds to `std::is_integral` in C++.
    // We will remove unnecessary bounds later.
    //
    // Maybe we should rename this to `PrimitiveInteger` or something, as it probably won't be used in the
    // same way as the original ACL.
    pub trait Integral:
        'static
        + Send
        + Sync
        + Copy
        + Ord
        + Not<Output = Self>
        + Add<Output = Self>
        + Sub<Output = Self>
        + Mul<Output = Self>
        + Div<Output = Self>
        + Rem<Output = Self>
        + AddAssign
        + SubAssign
        + MulAssign
        + DivAssign
        + RemAssign
        + Sum
        + Product
        + BitOr<Output = Self>
        + BitAnd<Output = Self>
        + BitXor<Output = Self>
        + BitOrAssign
        + BitAndAssign
        + BitXorAssign
        + Shl<Output = Self>
        + Shr<Output = Self>
        + ShlAssign
        + ShrAssign
        + fmt::Display
        + fmt::Debug
        + fmt::Binary
        + fmt::Octal
        + Zero
        + One
        + BoundedBelow
        + BoundedAbove
    {
    }

    /// Class that has additive identity element
    pub trait Zero {
        /// The additive identity element
        fn zero() -> Self;
    }

    /// Class that has multiplicative identity element
    pub trait One {
        /// The multiplicative identity element
        fn one() -> Self;
    }

    pub trait BoundedBelow {
        fn min_value() -> Self;
    }

    pub trait BoundedAbove {
        fn max_value() -> Self;
    }

    macro_rules! impl_integral {
    ($($ty:ty),*) => {
        $(
            impl Zero for $ty {
                #[inline]
                fn zero() -> Self {
                    0
                }
            }

            impl One for $ty {
                #[inline]
                fn one() -> Self {
                    1
                }
            }

            impl BoundedBelow for $ty {
                #[inline]
                fn min_value() -> Self {
                    Self::min_value()
                }
            }

            impl BoundedAbove for $ty {
                #[inline]
                fn max_value() -> Self {
                    Self::max_value()
                }
            }

            impl Integral for $ty {}
        )*
    };
}

    impl_integral!(i8, i16, i32, i64, i128, isize, u8, u16, u32, u64, u128, usize);
}
pub mod lazysegtree {
    use crate::internal_bit::ceil_pow2;
    use crate::Monoid;

    pub trait MapMonoid {
        type M: Monoid;
        type F: Clone;
        // type S = <Self::M as Monoid>::S;
        fn identity_element() -> <Self::M as Monoid>::S {
            Self::M::identity()
        }
        fn binary_operation(
            a: &<Self::M as Monoid>::S,
            b: &<Self::M as Monoid>::S,
        ) -> <Self::M as Monoid>::S {
            Self::M::binary_operation(a, b)
        }
        fn identity_map() -> Self::F;
        fn mapping(f: &Self::F, x: &<Self::M as Monoid>::S) -> <Self::M as Monoid>::S;
        fn composition(f: &Self::F, g: &Self::F) -> Self::F;
    }

    impl<F: MapMonoid> Default for LazySegtree<F> {
        fn default() -> Self {
            Self::new(0)
        }
    }
    impl<F: MapMonoid> LazySegtree<F> {
        pub fn new(n: usize) -> Self {
            vec![F::identity_element(); n].into()
        }
    }
    impl<F: MapMonoid> From<Vec<<F::M as Monoid>::S>> for LazySegtree<F> {
        fn from(v: Vec<<F::M as Monoid>::S>) -> Self {
            let n = v.len();
            let log = ceil_pow2(n as u32) as usize;
            let size = 1 << log;
            let mut d = vec![F::identity_element(); 2 * size];
            let lz = vec![F::identity_map(); size];
            d[size..(size + n)].clone_from_slice(&v);
            let mut ret = LazySegtree {
                n,
                size,
                log,
                d,
                lz,
            };
            for i in (1..size).rev() {
                ret.update(i);
            }
            ret
        }
    }

    impl<F: MapMonoid> LazySegtree<F> {
        pub fn set(&mut self, mut p: usize, x: <F::M as Monoid>::S) {
            assert!(p < self.n);
            p += self.size;
            for i in (1..=self.log).rev() {
                self.push(p >> i);
            }
            self.d[p] = x;
            for i in 1..=self.log {
                self.update(p >> i);
            }
        }

        pub fn get(&mut self, mut p: usize) -> <F::M as Monoid>::S {
            assert!(p < self.n);
            p += self.size;
            for i in (1..=self.log).rev() {
                self.push(p >> i);
            }
            self.d[p].clone()
        }

        pub fn prod(&mut self, mut l: usize, mut r: usize) -> <F::M as Monoid>::S {
            assert!(l <= r && r <= self.n);
            if l == r {
                return F::identity_element();
            }

            l += self.size;
            r += self.size;

            for i in (1..=self.log).rev() {
                if ((l >> i) << i) != l {
                    self.push(l >> i);
                }
                if ((r >> i) << i) != r {
                    self.push(r >> i);
                }
            }

            let mut sml = F::identity_element();
            let mut smr = F::identity_element();
            while l < r {
                if l & 1 != 0 {
                    sml = F::binary_operation(&sml, &self.d[l]);
                    l += 1;
                }
                if r & 1 != 0 {
                    r -= 1;
                    smr = F::binary_operation(&self.d[r], &smr);
                }
                l >>= 1;
                r >>= 1;
            }

            F::binary_operation(&sml, &smr)
        }

        pub fn all_prod(&self) -> <F::M as Monoid>::S {
            self.d[1].clone()
        }

        pub fn apply(&mut self, mut p: usize, f: F::F) {
            assert!(p < self.n);
            p += self.size;
            for i in (1..=self.log).rev() {
                self.push(p >> i);
            }
            self.d[p] = F::mapping(&f, &self.d[p]);
            for i in 1..=self.log {
                self.update(p >> i);
            }
        }
        pub fn apply_range(&mut self, mut l: usize, mut r: usize, f: F::F) {
            assert!(l <= r && r <= self.n);
            if l == r {
                return;
            }

            l += self.size;
            r += self.size;

            for i in (1..=self.log).rev() {
                if ((l >> i) << i) != l {
                    self.push(l >> i);
                }
                if ((r >> i) << i) != r {
                    self.push((r - 1) >> i);
                }
            }

            {
                let l2 = l;
                let r2 = r;
                while l < r {
                    if l & 1 != 0 {
                        self.all_apply(l, f.clone());
                        l += 1;
                    }
                    if r & 1 != 0 {
                        r -= 1;
                        self.all_apply(r, f.clone());
                    }
                    l >>= 1;
                    r >>= 1;
                }
                l = l2;
                r = r2;
            }

            for i in 1..=self.log {
                if ((l >> i) << i) != l {
                    self.update(l >> i);
                }
                if ((r >> i) << i) != r {
                    self.update((r - 1) >> i);
                }
            }
        }

        pub fn max_right<G>(&mut self, mut l: usize, g: G) -> usize
        where
            G: Fn(<F::M as Monoid>::S) -> bool,
        {
            assert!(l <= self.n);
            assert!(g(F::identity_element()));
            if l == self.n {
                return self.n;
            }
            l += self.size;
            for i in (1..=self.log).rev() {
                self.push(l >> i);
            }
            let mut sm = F::identity_element();
            while {
                // do
                while l % 2 == 0 {
                    l >>= 1;
                }
                if !g(F::binary_operation(&sm, &self.d[l])) {
                    while l < self.size {
                        self.push(l);
                        l *= 2;
                        let res = F::binary_operation(&sm, &self.d[l]);
                        if g(res.clone()) {
                            sm = res;
                            l += 1;
                        }
                    }
                    return l - self.size;
                }
                sm = F::binary_operation(&sm, &self.d[l]);
                l += 1;
                //while
                {
                    let l = l as isize;
                    (l & -l) != l
                }
            } {}
            self.n
        }

        pub fn min_left<G>(&mut self, mut r: usize, g: G) -> usize
        where
            G: Fn(<F::M as Monoid>::S) -> bool,
        {
            assert!(r <= self.n);
            assert!(g(F::identity_element()));
            if r == 0 {
                return 0;
            }
            r += self.size;
            for i in (1..=self.log).rev() {
                self.push((r - 1) >> i);
            }
            let mut sm = F::identity_element();
            while {
                // do
                r -= 1;
                while r > 1 && r % 2 != 0 {
                    r >>= 1;
                }
                if !g(F::binary_operation(&self.d[r], &sm)) {
                    while r < self.size {
                        self.push(r);
                        r = 2 * r + 1;
                        let res = F::binary_operation(&self.d[r], &sm);
                        if g(res.clone()) {
                            sm = res;
                            r -= 1;
                        }
                    }
                    return r + 1 - self.size;
                }
                sm = F::binary_operation(&self.d[r], &sm);
                // while
                {
                    let r = r as isize;
                    (r & -r) != r
                }
            } {}
            0
        }
    }

    pub struct LazySegtree<F>
    where
        F: MapMonoid,
    {
        n: usize,
        size: usize,
        log: usize,
        d: Vec<<F::M as Monoid>::S>,
        lz: Vec<F::F>,
    }
    impl<F> LazySegtree<F>
    where
        F: MapMonoid,
    {
        fn update(&mut self, k: usize) {
            self.d[k] = F::binary_operation(&self.d[2 * k], &self.d[2 * k + 1]);
        }
        fn all_apply(&mut self, k: usize, f: F::F) {
            self.d[k] = F::mapping(&f, &self.d[k]);
            if k < self.size {
                self.lz[k] = F::composition(&f, &self.lz[k]);
            }
        }
        fn push(&mut self, k: usize) {
            self.all_apply(2 * k, self.lz[k].clone());
            self.all_apply(2 * k + 1, self.lz[k].clone());
            self.lz[k] = F::identity_map();
        }
    }

    // TODO is it useful?
    use std::fmt::{Debug, Error, Formatter, Write};
    impl<F> Debug for LazySegtree<F>
    where
        F: MapMonoid,
        F::F: Debug,
        <F::M as Monoid>::S: Debug,
    {
        fn fmt(&self, f: &mut Formatter<'_>) -> Result<(), Error> {
            for i in 0..self.log {
                for j in 0..1 << i {
                    f.write_fmt(format_args!(
                        "{:?}[{:?}]\t",
                        self.d[(1 << i) + j],
                        self.lz[(1 << i) + j]
                    ))?;
                }
                f.write_char('\n')?;
            }
            for i in 0..self.size {
                f.write_fmt(format_args!("{:?}\t", self.d[self.size + i]))?;
            }
            Ok(())
        }
    }
}
pub mod lca {
    pub struct LcaTree<W> {
        g: Vec<Vec<(usize, W)>>,
        depth: Vec<usize>,
        pars: Vec<Vec<usize>>,
        dist: Vec<W>,
    }

    impl<W: crate::internal_type_traits::Integral> LcaTree<W> {
        pub fn new(g: Vec<Vec<(usize, W)>>) -> Self {
            Self::new_with_root(g, 0)
        }

        pub fn new_with_root(g: Vec<Vec<(usize, W)>>, root: usize) -> Self {
            let n = g.len();
            assert!(root < n);
            fn dfs<W: crate::internal_type_traits::Integral>(
                u: usize,
                p: Option<usize>,
                par: &mut Vec<usize>,
                depth: &mut Vec<usize>,
                dist: &mut Vec<W>,
                g: &Vec<Vec<(usize, W)>>,
            ) {
                for &(v, c) in &g[u] {
                    if Some(v) == p {
                        continue;
                    }
                    par[v] = u;
                    depth[v] = depth[u] + 1;
                    dist[v] = dist[u] + c;
                    dfs(v, Some(u), par, depth, dist, g);
                }
            }
            let mut par = vec![root; n];
            let mut depth = vec![0; n];
            let mut dist = vec![W::zero(); n];

            dfs(root, None, &mut par, &mut depth, &mut dist, &g);
            let mut k = 0;
            while (1 << k) < n {
                k += 1;
            }

            let mut pars = vec![vec![0; n]; k];
            pars[0] = par;
            for i in 0..k - 1 {
                for u in 0..n {
                    pars[i + 1][u] = pars[i][pars[i][u]];
                }
            }

            Self {
                g,
                depth,
                pars,
                dist,
            }
        }

        pub fn lca(&self, u: usize, v: usize) -> usize {
            let n = self.g.len();
            assert!(u < n && v < n);
            let (mut u, mut v) = if self.depth[u] < self.depth[v] {
                (u, v)
            } else {
                (v, u)
            };

            let d = self.depth[v] - self.depth[u];
            for i in 0..self.pars.len() {
                if d >> i & 1 == 1 {
                    v = self.pars[i][v];
                }
            }

            if v == u {
                return v;
            }

            for i in (0..self.pars.len()).rev() {
                if self.pars[i][u] != self.pars[i][v] {
                    u = self.pars[i][u];
                    v = self.pars[i][v];
                }
            }

            return self.pars[0][u];
        }

        pub fn dist(&self, u: usize, v: usize) -> W {
            let l = self.lca(u, v);
            return self.dist[u] + self.dist[v] - (W::one() + W::one()) * self.dist[l];
        }
    }
}
pub mod math {
    //! Number-theoretic algorithms.

    use crate::internal_math;

    use std::mem::swap;

    /// Returns $x^n \bmod m$.
    ///
    /// # Constraints
    ///
    /// - $0 \leq n$
    /// - $1 \leq m$
    ///
    /// # Panics
    ///
    /// Panics if the above constraints are not satisfied.
    ///
    /// # Complexity
    ///
    /// - $O(\log n)$
    ///
    /// # Example
    ///
    /// ```
    /// use ac_library_rs::math;
    ///
    /// assert_eq!(math::pow_mod(2, 10000, 7), 2);
    /// ```
    #[allow(clippy::many_single_char_names)]
    pub fn pow_mod(x: i64, mut n: i64, m: u32) -> u32 {
        assert!(0 <= n && 1 <= m && m <= 2u32.pow(31));
        if m == 1 {
            return 0;
        }
        let bt = internal_math::Barrett::new(m);
        let mut r = 1;
        let mut y = internal_math::safe_mod(x, m as i64) as u32;
        while n != 0 {
            if n & 1 != 0 {
                r = bt.mul(r, y);
            }
            y = bt.mul(y, y);
            n >>= 1;
        }
        r
    }

    /// Returns an integer $y \in [0, m)$ such that $xy \equiv 1 \pmod m$.
    ///
    /// # Constraints
    ///
    /// - $\gcd(x, m) = 1$
    /// - $1 \leq m$
    ///
    /// # Panics
    ///
    /// Panics if the above constraints are not satisfied.
    ///
    /// # Complexity
    ///
    /// - $O(\log m)$
    ///
    /// # Example
    ///
    /// ```
    /// use ac_library_rs::math;
    ///
    /// assert_eq!(math::inv_mod(3, 7), 5);
    /// ```
    pub fn inv_mod(x: i64, m: i64) -> i64 {
        assert!(1 <= m);
        let z = internal_math::inv_gcd(x, m);
        assert!(z.0 == 1);
        z.1
    }

    /// Performs CRT (Chinese Remainder Theorem).
    ///
    /// Given two sequences $r, m$ of length $n$, this function solves the modular equation system
    ///
    /// \\[
    ///   x \equiv r_i \pmod{m_i}, \forall i \in \\{0, 1, \cdots, n - 1\\}
    /// \\]
    ///
    /// If there is no solution, it returns $(0, 0)$.
    ///
    /// Otherwise, all of the solutions can be written as the form $x \equiv y \pmod z$, using integer $y, z\\ (0 \leq y < z = \text{lcm}(m))$.
    /// It returns this $(y, z)$.
    ///
    /// If $n = 0$, it returns $(0, 1)$.
    ///
    /// # Constraints
    ///
    /// - $|r| = |m|$
    /// - $1 \leq m_{\forall i}$
    /// - $\text{lcm}(m)$ is in `i64`
    ///
    /// # Panics
    ///
    /// Panics if the above constraints are not satisfied.
    ///
    /// # Complexity
    ///
    /// - $O(n \log \text{lcm}(m))$
    ///
    /// # Example
    ///
    /// ```
    /// use ac_library_rs::math;
    ///
    /// let r = [2, 3, 2];
    /// let m = [3, 5, 7];
    /// assert_eq!(math::crt(&r, &m), (23, 105));
    /// ```
    pub fn crt(r: &[i64], m: &[i64]) -> (i64, i64) {
        assert_eq!(r.len(), m.len());
        // Contracts: 0 <= r0 < m0
        let (mut r0, mut m0) = (0, 1);
        for (&(mut ri), &(mut mi)) in r.iter().zip(m.iter()) {
            assert!(1 <= mi);
            ri = internal_math::safe_mod(ri, mi);
            if m0 < mi {
                swap(&mut r0, &mut ri);
                swap(&mut m0, &mut mi);
            }
            if m0 % mi == 0 {
                if r0 % mi != ri {
                    return (0, 0);
                }
                continue;
            }
            // assume: m0 > mi, lcm(m0, mi) >= 2 * max(m0, mi)

            // (r0, m0), (ri, mi) -> (r2, m2 = lcm(m0, m1));
            // r2 % m0 = r0
            // r2 % mi = ri
            // -> (r0 + x*m0) % mi = ri
            // -> x*u0*g % (u1*g) = (ri - r0) (u0*g = m0, u1*g = mi)
            // -> x = (ri - r0) / g * inv(u0) (mod u1)

            // im = inv(u0) (mod u1) (0 <= im < u1)
            let (g, im) = internal_math::inv_gcd(m0, mi);
            let u1 = mi / g;
            // |ri - r0| < (m0 + mi) <= lcm(m0, mi)
            if (ri - r0) % g != 0 {
                return (0, 0);
            }
            // u1 * u1 <= mi * mi / g / g <= m0 * mi / g = lcm(m0, mi)
            let x = (ri - r0) / g % u1 * im % u1;

            // |r0| + |m0 * x|
            // < m0 + m0 * (u1 - 1)
            // = m0 + m0 * mi / g - m0
            // = lcm(m0, mi)
            r0 += x * m0;
            m0 *= u1; // -> lcm(m0, mi)
            if r0 < 0 {
                r0 += m0
            };
        }

        (r0, m0)
    }

    /// Returns $\sum_{i = 0}^{n - 1} \lfloor \frac{a \times i + b}{m} \rfloor$.
    ///
    /// # Constraints
    ///
    /// - $0 \leq n \leq 10^9$
    /// - $1 \leq m \leq 10^9$
    /// - $0 \leq a, b \leq m$
    ///
    /// # Panics
    ///
    /// Panics if the above constraints are not satisfied and overflow or division by zero occurred.
    ///
    /// # Complexity
    ///
    /// - $O(\log(n + m + a + b))$
    ///
    /// # Example
    ///
    /// ```
    /// use ac_library_rs::math;
    ///
    /// assert_eq!(math::floor_sum(6, 5, 4, 3), 13);
    /// ```
    pub fn floor_sum(n: i64, m: i64, mut a: i64, mut b: i64) -> i64 {
        let mut ans = 0;
        if a >= m {
            ans += (n - 1) * n * (a / m) / 2;
            a %= m;
        }
        if b >= m {
            ans += n * (b / m);
            b %= m;
        }

        let y_max = (a * n + b) / m;
        let x_max = y_max * m - b;
        if y_max == 0 {
            return ans;
        }
        ans += (n - (x_max + a - 1) / a) * y_max;
        ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
        ans
    }
}
pub mod maxflow {
    #![allow(dead_code)]
    use crate::internal_queue::SimpleQueue;
    use crate::internal_type_traits::Integral;
    use std::cmp::min;
    use std::iter;

    impl<Cap> MfGraph<Cap>
    where
        Cap: Integral,
    {
        pub fn new(n: usize) -> MfGraph<Cap> {
            MfGraph {
                _n: n,
                pos: Vec::new(),
                g: iter::repeat_with(Vec::new).take(n).collect(),
            }
        }

        pub fn add_edge(&mut self, from: usize, to: usize, cap: Cap) -> usize {
            assert!(from < self._n);
            assert!(to < self._n);
            assert!(Cap::zero() <= cap);
            let m = self.pos.len();
            self.pos.push((from, self.g[from].len()));
            let rev = self.g[to].len() + if from == to { 1 } else { 0 };
            self.g[from].push(_Edge { to, rev, cap });
            let rev = self.g[from].len() - 1;
            self.g[to].push(_Edge {
                to: from,
                rev,
                cap: Cap::zero(),
            });
            m
        }
    }

    #[derive(Debug, PartialEq, Eq)]
    pub struct Edge<Cap: Integral> {
        pub from: usize,
        pub to: usize,
        pub cap: Cap,
        pub flow: Cap,
    }

    impl<Cap> MfGraph<Cap>
    where
        Cap: Integral,
    {
        pub fn get_edge(&self, i: usize) -> Edge<Cap> {
            let m = self.pos.len();
            assert!(i < m);
            let _e = &self.g[self.pos[i].0][self.pos[i].1];
            let _re = &self.g[_e.to][_e.rev];
            Edge {
                from: self.pos[i].0,
                to: _e.to,
                cap: _e.cap + _re.cap,
                flow: _re.cap,
            }
        }
        pub fn edges(&self) -> Vec<Edge<Cap>> {
            let m = self.pos.len();
            (0..m).map(|i| self.get_edge(i)).collect()
        }
        pub fn change_edge(&mut self, i: usize, new_cap: Cap, new_flow: Cap) {
            let m = self.pos.len();
            assert!(i < m);
            assert!(Cap::zero() <= new_flow && new_flow <= new_cap);
            let (to, rev) = {
                let _e = &mut self.g[self.pos[i].0][self.pos[i].1];
                _e.cap = new_cap - new_flow;
                (_e.to, _e.rev)
            };
            let _re = &mut self.g[to][rev];
            _re.cap = new_flow;
        }

        /// `s != t` must hold, otherwise it panics.
        pub fn flow(&mut self, s: usize, t: usize) -> Cap {
            self.flow_with_capacity(s, t, Cap::max_value())
        }
        /// # Parameters
        /// * `s != t` must hold, otherwise it panics.
        /// * `flow_limit >= 0`
        pub fn flow_with_capacity(&mut self, s: usize, t: usize, flow_limit: Cap) -> Cap {
            let n_ = self._n;
            assert!(s < n_);
            assert!(t < n_);
            // By the definition of max flow in appendix.html, this function should return 0
            // when the same vertices are provided.  On the other hand, it is reasonable to
            // return infinity-like value too, which is what the original implementation
            // (and this implementation without the following assertion) does.
            // Since either return value is confusing, we'd rather deny the parameters
            // of the two same vertices.
            // For more details, see https://github.com/rust-lang-ja/ac-library-rs/pull/24#discussion_r485343451
            // and https://github.com/atcoder/ac-library/issues/5 .
            assert_ne!(s, t);
            // Additional constraint
            assert!(Cap::zero() <= flow_limit);

            let mut calc = FlowCalculator {
                graph: self,
                s,
                t,
                flow_limit,
                level: vec![0; n_],
                iter: vec![0; n_],
                que: SimpleQueue::default(),
            };

            let mut flow = Cap::zero();
            while flow < flow_limit {
                calc.bfs();
                if calc.level[t] == -1 {
                    break;
                }
                calc.iter.iter_mut().for_each(|e| *e = 0);
                while flow < flow_limit {
                    let f = calc.dfs(t, flow_limit - flow);
                    if f == Cap::zero() {
                        break;
                    }
                    flow += f;
                }
            }
            flow
        }

        pub fn min_cut(&self, s: usize) -> Vec<bool> {
            let mut visited = vec![false; self._n];
            let mut que = SimpleQueue::default();
            que.push(s);
            while let Some(&p) = que.pop() {
                visited[p] = true;
                for e in &self.g[p] {
                    if e.cap != Cap::zero() && !visited[e.to] {
                        visited[e.to] = true;
                        que.push(e.to);
                    }
                }
            }
            visited
        }
    }

    struct FlowCalculator<'a, Cap> {
        graph: &'a mut MfGraph<Cap>,
        s: usize,
        t: usize,
        flow_limit: Cap,
        level: Vec<i32>,
        iter: Vec<usize>,
        que: SimpleQueue<usize>,
    }

    impl<Cap> FlowCalculator<'_, Cap>
    where
        Cap: Integral,
    {
        fn bfs(&mut self) {
            self.level.iter_mut().for_each(|e| *e = -1);
            self.level[self.s] = 0;
            self.que.clear();
            self.que.push(self.s);
            while !self.que.empty() {
                let v = *self.que.front().unwrap();
                self.que.pop();
                for e in &self.graph.g[v] {
                    if e.cap == Cap::zero() || self.level[e.to] >= 0 {
                        continue;
                    }
                    self.level[e.to] = self.level[v] + 1;
                    if e.to == self.t {
                        return;
                    }
                    self.que.push(e.to);
                }
            }
        }
        fn dfs(&mut self, v: usize, up: Cap) -> Cap {
            if v == self.s {
                return up;
            }
            let mut res = Cap::zero();
            let level_v = self.level[v];
            for i in self.iter[v]..self.graph.g[v].len() {
                self.iter[v] = i;
                let &_Edge {
                    to: e_to,
                    rev: e_rev,
                    ..
                } = &self.graph.g[v][i];
                if level_v <= self.level[e_to] || self.graph.g[e_to][e_rev].cap == Cap::zero() {
                    continue;
                }
                let d = self.dfs(e_to, min(up - res, self.graph.g[e_to][e_rev].cap));
                if d <= Cap::zero() {
                    continue;
                }
                self.graph.g[v][i].cap += d;
                self.graph.g[e_to][e_rev].cap -= d;
                res += d;
                if res == up {
                    return res;
                }
            }
            self.iter[v] = self.graph.g[v].len();
            res
        }
    }

    #[derive(Default)]
    pub struct MfGraph<Cap> {
        _n: usize,
        pos: Vec<(usize, usize)>,
        g: Vec<Vec<_Edge<Cap>>>,
    }

    struct _Edge<Cap> {
        to: usize,
        rev: usize,
        cap: Cap,
    }
}
pub mod mincostflow {
    use crate::internal_type_traits::Integral;

    pub struct MinCostFlowEdge<T> {
        pub from: usize,
        pub to: usize,
        pub cap: T,
        pub flow: T,
        pub cost: T,
    }

    pub struct MinCostFlowGraph<T> {
        pos: Vec<(usize, usize)>,
        g: Vec<Vec<_Edge<T>>>,
    }

    impl<T> MinCostFlowGraph<T>
    where
        T: Integral + std::ops::Neg<Output = T>,
    {
        pub fn new(n: usize) -> Self {
            Self {
                pos: vec![],
                g: (0..n).map(|_| vec![]).collect(),
            }
        }

        pub fn get_edge(&self, i: usize) -> MinCostFlowEdge<T> {
            assert!(i < self.pos.len());
            let e = &self.g[self.pos[i].0][self.pos[i].1];
            let re = &self.g[e.to][e.rev];
            MinCostFlowEdge {
                from: self.pos[i].0,
                to: e.to,
                cap: e.cap + re.cap,
                flow: re.cap,
                cost: e.cost,
            }
        }

        pub fn edges(&self) -> Vec<MinCostFlowEdge<T>> {
            let m = self.pos.len();
            let mut result = vec![];
            for i in 0..m {
                result.push(self.get_edge(i));
            }
            result
        }

        pub fn add_edge(&mut self, from: usize, to: usize, cap: T, cost: T) -> usize {
            assert!(from < self.g.len());
            assert!(to < self.g.len());
            assert_ne!(from, to);
            assert!(cap >= T::zero());
            assert!(cost >= T::zero());

            self.pos.push((from, self.g[from].len()));

            let rev = self.g[to].len();
            self.g[from].push(_Edge { to, rev, cap, cost });

            let rev = self.g[from].len() - 1;
            self.g[to].push(_Edge {
                to: from,
                rev,
                cap: T::zero(),
                cost: -cost,
            });

            self.pos.len() - 1
        }

        /// Returns (maximum flow, cost)
        pub fn flow(&mut self, source: usize, sink: usize, flow_limit: T) -> (T, T) {
            self.slope(source, sink, flow_limit).pop().unwrap()
        }

        pub fn slope(&mut self, source: usize, sink: usize, flow_limit: T) -> Vec<(T, T)> {
            let n = self.g.len();
            assert!(source < n);
            assert!(sink < n);
            assert_ne!(source, sink);

            let mut dual = vec![T::zero(); n];
            let mut prev_v = vec![0; n];
            let mut prev_e = vec![0; n];
            let mut flow = T::zero();
            let mut cost = T::zero();
            let mut prev_cost_per_flow: Option<T> = None;
            let mut result = vec![(flow, cost)];
            while flow < flow_limit {
                if !self.refine_dual(source, sink, &mut dual, &mut prev_v, &mut prev_e) {
                    break;
                }

                let mut c = flow_limit - flow;
                let mut v = sink;
                while v != source {
                    c = std::cmp::min(c, self.g[prev_v[v]][prev_e[v]].cap);
                    v = prev_v[v];
                }

                let mut v = sink;
                while v != source {
                    self.g[prev_v[v]][prev_e[v]].cap -= c;
                    let rev = self.g[prev_v[v]][prev_e[v]].rev;
                    self.g[v][rev].cap += c;
                    v = prev_v[v];
                }

                let d = -dual[source];
                flow += c;
                cost += d * c;
                if prev_cost_per_flow == Some(d) {
                    assert!(result.pop().is_some());
                }
                result.push((flow, cost));
                prev_cost_per_flow = Some(d);
            }
            result
        }

        fn refine_dual(
            &self,
            source: usize,
            sink: usize,
            dual: &mut [T],
            pv: &mut [usize],
            pe: &mut [usize],
        ) -> bool {
            let n = self.g.len();
            let mut dist = vec![T::max_value(); n];
            let mut vis = vec![false; n];

            let mut que = std::collections::BinaryHeap::new();
            dist[source] = T::zero();
            que.push((std::cmp::Reverse(T::zero()), source));
            while let Some((_, v)) = que.pop() {
                if vis[v] {
                    continue;
                }
                vis[v] = true;
                if v == sink {
                    break;
                }

                for (i, e) in self.g[v].iter().enumerate() {
                    if vis[e.to] || e.cap == T::zero() {
                        continue;
                    }

                    let cost = e.cost - dual[e.to] + dual[v];
                    if dist[e.to] - dist[v] > cost {
                        dist[e.to] = dist[v] + cost;
                        pv[e.to] = v;
                        pe[e.to] = i;
                        que.push((std::cmp::Reverse(dist[e.to]), e.to));
                    }
                }
            }

            if !vis[sink] {
                return false;
            }

            for v in 0..n {
                if !vis[v] {
                    continue;
                }
                dual[v] -= dist[sink] - dist[v];
            }
            true
        }
    }

    struct _Edge<T> {
        to: usize,
        rev: usize,
        cap: T,
        cost: T,
    }
}
pub mod modint {
    //! Structs that treat the modular arithmetic.
    //!
    //! For most of the problems, It is sufficient to use [`ModInt1000000007`] or [`ModInt998244353`], which can be used as follows.
    //!
    //! ```
    //! use ac_library_rs::ModInt1000000007 as Mint; // rename to whatever you want
    //! use proconio::{input, source::once::OnceSource};
    //!
    //! input! {
    //!     from OnceSource::from("1000000006 2\n"),
    //!     a: Mint,
    //!     b: Mint,
    //! }
    //!
    //! println!("{}", a + b); // `1`
    //! ```
    //!
    //! If the modulus is not fixed, you can use [`ModInt`] as follows.
    //!
    //! ```
    //! use ac_library_rs::ModInt as Mint; // rename to whatever you want
    //! use proconio::{input, source::once::OnceSource};
    //!
    //! input! {
    //!     from OnceSource::from("3 3 7\n"),
    //!     a: u32,
    //!     b: u32,
    //!     m: u32,
    //! }
    //!
    //! Mint::set_modulus(m);
    //! let a = Mint::new(a);
    //! let b = Mint::new(b);
    //!
    //! println!("{}", a * b); // `2`
    //! ```
    //!
    //! # Major changes from the original ACL
    //!
    //! - Converted the struct names to PascalCase.
    //! - Renamed `mod` → `modulus`.
    //! - Moduli are `u32`, not `i32`.
    //! - Each `Id` does not have a identifier number. Instead, they explicitly own `&'static LocalKey<RefCell<Barrett>>`.
    //! - The type of the argument of `pow` is `u64`, not `i64`.
    //! - Modints implement `FromStr` and `Display`. Modints in the original ACL don't have `operator<<` or `operator>>`.
    //!
    //! [`ModInt1000000007`]: ./type.ModInt1000000007.html
    //! [`ModInt998244353`]: ./type.ModInt998244353.html
    //! [`ModInt`]: ./type.ModInt.html

    use crate::internal_math;
    use std::{
        cell::RefCell,
        convert::{Infallible, TryInto as _},
        fmt,
        hash::{Hash, Hasher},
        iter::{Product, Sum},
        marker::PhantomData,
        ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign},
        str::FromStr,
        sync::atomic::{self, AtomicU32, AtomicU64},
        thread::LocalKey,
    };

    pub type ModInt1000000007 = StaticModInt<Mod1000000007>;
    pub type ModInt998244353 = StaticModInt<Mod998244353>;
    pub type ModInt = DynamicModInt<DefaultId>;

    /// Represents _ℤ/mℤ_ where _m_ is a constant value.
    ///
    /// Corresponds to `atcoder::static_modint` in the original ACL.
    ///
    /// # Example
    ///
    /// ```
    /// use ac_library_rs::ModInt1000000007 as Mint;
    /// use proconio::{input, source::once::OnceSource};
    ///
    /// input! {
    ///     from OnceSource::from("1000000006 2\n"),
    ///     a: Mint,
    ///     b: Mint,
    /// }
    ///
    /// println!("{}", a + b); // `1`
    /// ```
    #[derive(Copy, Clone, Eq, PartialEq)]
    #[repr(transparent)]
    pub struct StaticModInt<M> {
        val: u32,
        phantom: PhantomData<fn() -> M>,
    }

    impl<M: Modulus> StaticModInt<M> {
        /// Returns the modulus, which is [`<M as Modulus>::VALUE`].
        ///
        /// Corresponds to `atcoder::static_modint::mod` in the original ACL.
        ///
        /// # Example
        ///
        /// ```
        /// use ac_library_rs::ModInt1000000007 as Mint;
        ///
        /// assert_eq!(1_000_000_007, Mint::modulus());
        /// ```
        ///
        /// [`<M as Modulus>::VALUE`]: ../trait.Modulus.html#associatedconstant.VALUE
        #[inline(always)]
        pub fn modulus() -> u32 {
            M::VALUE
        }

        /// Creates a new `StaticModInt`.
        ///
        /// Takes [any primitive integer].
        ///
        /// Corresponds to the constructor of `atcoder::static_modint` in the original ACL.
        ///
        /// [any primitive integer]:  ../trait.RemEuclidU32.html
        #[inline]
        pub fn new<T: RemEuclidU32>(val: T) -> Self {
            Self::raw(val.rem_euclid_u32(M::VALUE))
        }

        /// Constructs a `StaticModInt` from a `val < Self::modulus()` without checking it.
        ///
        /// Corresponds to `atcoder::static_modint::raw` in the original ACL.
        ///
        /// # Constraints
        ///
        /// - `val` is less than `Self::modulus()`
        ///
        /// See [`ModIntBase::raw`] for more more details.
        ///
        /// [`ModIntBase::raw`]: ./trait.ModIntBase.html#tymethod.raw
        #[inline]
        pub fn raw(val: u32) -> Self {
            Self {
                val,
                phantom: PhantomData,
            }
        }

        /// Retruns the representative.
        ///
        /// Corresponds to `atcoder::static_modint::val` in the original ACL.
        #[inline]
        pub fn val(self) -> u32 {
            self.val
        }

        /// Returns `self` to the power of `n`.
        ///
        /// Corresponds to `atcoder::static_modint::pow` in the original ACL.
        #[inline]
        pub fn pow(self, n: u64) -> Self {
            <Self as ModIntBase>::pow(self, n)
        }

        /// Retruns the multiplicative inverse of `self`.
        ///
        /// Corresponds to `atcoder::static_modint::inv` in the original ACL.
        ///
        /// # Panics
        ///
        /// Panics if the multiplicative inverse does not exist.
        #[inline]
        pub fn inv(self) -> Self {
            if M::HINT_VALUE_IS_PRIME {
                if self.val() == 0 {
                    panic!("attempt to divide by zero");
                }
                debug_assert!(
                    internal_math::is_prime(M::VALUE.try_into().unwrap()),
                    "{} is not a prime number",
                    M::VALUE,
                );
                self.pow((M::VALUE - 2).into())
            } else {
                Self::inv_for_non_prime_modulus(self)
            }
        }
    }

    /// These methods are implemented for the struct.
    /// You don't need to `use` `ModIntBase` to call methods of `StaticModInt`.
    impl<M: Modulus> ModIntBase for StaticModInt<M> {
        #[inline(always)]
        fn modulus() -> u32 {
            Self::modulus()
        }

        #[inline]
        fn raw(val: u32) -> Self {
            Self::raw(val)
        }

        #[inline]
        fn val(self) -> u32 {
            self.val()
        }

        #[inline]
        fn inv(self) -> Self {
            self.inv()
        }
    }

    /// Represents a modulus.
    ///
    /// # Example
    ///
    /// ```
    /// macro_rules! modulus {
    ///     ($($name:ident($value:expr, $is_prime:expr)),*) => {
    ///         $(
    ///             #[derive(Copy, Clone, Eq, PartialEq)]
    ///             enum $name {}
    ///
    ///             impl ac_library_rs::modint::Modulus for $name {
    ///                 const VALUE: u32 = $value;
    ///                 const HINT_VALUE_IS_PRIME: bool = $is_prime;
    ///
    ///                 fn butterfly_cache() -> &'static ::std::thread::LocalKey<::std::cell::RefCell<::std::option::Option<ac_library_rs::modint::ButterflyCache<Self>>>> {
    ///                     thread_local! {
    ///                         static BUTTERFLY_CACHE: ::std::cell::RefCell<::std::option::Option<ac_library_rs::modint::ButterflyCache<$name>>> = ::std::default::Default::default();
    ///                     }
    ///                     &BUTTERFLY_CACHE
    ///                 }
    ///             }
    ///         )*
    ///     };
    /// }
    ///
    /// use ac_library_rs::StaticModInt;
    ///
    /// modulus!(Mod101(101, true), Mod103(103, true));
    ///
    /// type Z101 = StaticModInt<Mod101>;
    /// type Z103 = StaticModInt<Mod103>;
    ///
    /// assert_eq!(Z101::new(101), Z101::new(0));
    /// assert_eq!(Z103::new(103), Z103::new(0));
    /// ```
    pub trait Modulus: 'static + Copy + Eq {
        const VALUE: u32;
        const HINT_VALUE_IS_PRIME: bool;

        fn butterfly_cache() -> &'static LocalKey<RefCell<Option<ButterflyCache<Self>>>>;
    }

    /// Represents _1000000007_.
    #[derive(Copy, Clone, Ord, PartialOrd, Eq, PartialEq, Hash, Debug)]
    pub enum Mod1000000007 {}

    impl Modulus for Mod1000000007 {
        const VALUE: u32 = 1_000_000_007;
        const HINT_VALUE_IS_PRIME: bool = true;

        fn butterfly_cache() -> &'static LocalKey<RefCell<Option<ButterflyCache<Self>>>> {
            thread_local! {
                static BUTTERFLY_CACHE: RefCell<Option<ButterflyCache<Mod1000000007>>> = RefCell::default();
            }
            &BUTTERFLY_CACHE
        }
    }

    /// Represents _998244353_.
    #[derive(Copy, Clone, Ord, PartialOrd, Eq, PartialEq, Hash, Debug)]
    pub enum Mod998244353 {}

    impl Modulus for Mod998244353 {
        const VALUE: u32 = 998_244_353;
        const HINT_VALUE_IS_PRIME: bool = true;

        fn butterfly_cache() -> &'static LocalKey<RefCell<Option<ButterflyCache<Self>>>> {
            thread_local! {
                static BUTTERFLY_CACHE: RefCell<Option<ButterflyCache<Mod998244353>>> = RefCell::default();
            }
            &BUTTERFLY_CACHE
        }
    }

    /// Cache for butterfly operations.
    pub struct ButterflyCache<M> {
        pub(crate) sum_e: Vec<StaticModInt<M>>,
        pub(crate) sum_ie: Vec<StaticModInt<M>>,
    }

    /// Represents _ℤ/mℤ_ where _m_ is a dynamic value.
    ///
    /// Corresponds to `atcoder::dynamic_modint` in the original ACL.
    ///
    /// # Example
    ///
    /// ```
    /// use ac_library_rs::ModInt as Mint;
    /// use proconio::{input, source::once::OnceSource};
    ///
    /// input! {
    ///     from OnceSource::from("3 3 7\n"),
    ///     a: u32,
    ///     b: u32,
    ///     m: u32,
    /// }
    ///
    /// Mint::set_modulus(m);
    /// let a = Mint::new(a);
    /// let b = Mint::new(b);
    ///
    /// println!("{}", a * b); // `2`
    /// ```
    #[derive(Copy, Clone, Eq, PartialEq)]
    #[repr(transparent)]
    pub struct DynamicModInt<I> {
        val: u32,
        phantom: PhantomData<fn() -> I>,
    }

    impl<I: Id> DynamicModInt<I> {
        /// Returns the modulus.
        ///
        /// Corresponds to `atcoder::dynamic_modint::mod` in the original ACL.
        ///
        /// # Example
        ///
        /// ```
        /// use ac_library_rs::ModInt as Mint;
        ///
        /// assert_eq!(998_244_353, Mint::modulus()); // default modulus
        /// ```
        #[inline]
        pub fn modulus() -> u32 {
            I::companion_barrett().umod()
        }

        /// Sets a modulus.
        ///
        /// Corresponds to `atcoder::dynamic_modint::set_mod` in the original ACL.
        ///
        /// # Constraints
        ///
        /// - This function must be called earlier than any other operation of `Self`.
        ///
        /// # Example
        ///
        /// ```
        /// use ac_library_rs::ModInt as Mint;
        ///
        /// Mint::set_modulus(7);
        /// assert_eq!(7, Mint::modulus());
        /// ```
        #[inline]
        pub fn set_modulus(modulus: u32) {
            if modulus == 0 {
                panic!("the modulus must not be 0");
            }
            I::companion_barrett().update(modulus);
        }

        /// Creates a new `DynamicModInt`.
        ///
        /// Takes [any primitive integer].
        ///
        /// Corresponds to the constructor of `atcoder::dynamic_modint` in the original ACL.
        ///
        /// [any primitive integer]:  ../trait.RemEuclidU32.html
        #[inline]
        pub fn new<T: RemEuclidU32>(val: T) -> Self {
            <Self as ModIntBase>::new(val)
        }

        /// Constructs a `DynamicModInt` from a `val < Self::modulus()` without checking it.
        ///
        /// Corresponds to `atcoder::dynamic_modint::raw` in the original ACL.
        ///
        /// # Constraints
        ///
        /// - `val` is less than `Self::modulus()`
        ///
        /// See [`ModIntBase::raw`] for more more details.
        ///
        /// [`ModIntBase::raw`]: ./trait.ModIntBase.html#tymethod.raw
        #[inline]
        pub fn raw(val: u32) -> Self {
            Self {
                val,
                phantom: PhantomData,
            }
        }

        /// Retruns the representative.
        ///
        /// Corresponds to `atcoder::static_modint::val` in the original ACL.
        #[inline]
        pub fn val(self) -> u32 {
            self.val
        }

        /// Returns `self` to the power of `n`.
        ///
        /// Corresponds to `atcoder::dynamic_modint::pow` in the original ACL.
        #[inline]
        pub fn pow(self, n: u64) -> Self {
            <Self as ModIntBase>::pow(self, n)
        }

        /// Retruns the multiplicative inverse of `self`.
        ///
        /// Corresponds to `atcoder::dynamic_modint::inv` in the original ACL.
        ///
        /// # Panics
        ///
        /// Panics if the multiplicative inverse does not exist.
        #[inline]
        pub fn inv(self) -> Self {
            Self::inv_for_non_prime_modulus(self)
        }
    }

    /// These methods are implemented for the struct.
    /// You don't need to `use` `ModIntBase` to call methods of `DynamicModInt`.
    impl<I: Id> ModIntBase for DynamicModInt<I> {
        #[inline]
        fn modulus() -> u32 {
            Self::modulus()
        }

        #[inline]
        fn raw(val: u32) -> Self {
            Self::raw(val)
        }

        #[inline]
        fn val(self) -> u32 {
            self.val()
        }

        #[inline]
        fn inv(self) -> Self {
            self.inv()
        }
    }

    pub trait Id: 'static + Copy + Eq {
        fn companion_barrett() -> &'static Barrett;
    }

    #[derive(Copy, Clone, Ord, PartialOrd, Eq, PartialEq, Hash, Debug)]
    pub enum DefaultId {}

    impl Id for DefaultId {
        fn companion_barrett() -> &'static Barrett {
            static BARRETT: Barrett = Barrett::default();
            &BARRETT
        }
    }

    /// Pair of _m_ and _ceil(2⁶⁴/m)_.
    pub struct Barrett {
        m: AtomicU32,
        im: AtomicU64,
    }

    impl Barrett {
        /// Creates a new `Barrett`.
        #[inline]
        pub const fn new(m: u32) -> Self {
            Self {
                m: AtomicU32::new(m),
                im: AtomicU64::new((-1i64 as u64 / m as u64).wrapping_add(1)),
            }
        }

        #[inline]
        const fn default() -> Self {
            Self::new(998_244_353)
        }

        #[inline]
        fn update(&self, m: u32) {
            let im = (-1i64 as u64 / m as u64).wrapping_add(1);
            self.m.store(m, atomic::Ordering::SeqCst);
            self.im.store(im, atomic::Ordering::SeqCst);
        }

        #[inline]
        fn umod(&self) -> u32 {
            self.m.load(atomic::Ordering::SeqCst)
        }

        #[inline]
        fn mul(&self, a: u32, b: u32) -> u32 {
            let m = self.m.load(atomic::Ordering::SeqCst);
            let im = self.im.load(atomic::Ordering::SeqCst);
            internal_math::mul_mod(a, b, m, im)
        }
    }

    impl Default for Barrett {
        #[inline]
        fn default() -> Self {
            Self::default()
        }
    }

    /// A trait for [`StaticModInt`] and [`DynamicModInt`].
    ///
    /// Corresponds to `atcoder::internal::modint_base` in the original ACL.
    ///
    /// [`StaticModInt`]: ../struct.StaticModInt.html
    /// [`DynamicModInt`]: ../struct.DynamicModInt.html
    pub trait ModIntBase:
        Default
        + FromStr
        + From<i8>
        + From<i16>
        + From<i32>
        + From<i64>
        + From<i128>
        + From<isize>
        + From<u8>
        + From<u16>
        + From<u32>
        + From<u64>
        + From<u128>
        + From<usize>
        + Copy
        + Eq
        + Hash
        + fmt::Display
        + fmt::Debug
        + Neg<Output = Self>
        + Add<Output = Self>
        + Sub<Output = Self>
        + Mul<Output = Self>
        + Div<Output = Self>
        + AddAssign
        + SubAssign
        + MulAssign
        + DivAssign
    {
        /// Returns the modulus.
        ///
        /// Corresponds to `atcoder::static_modint::mod` and `atcoder::dynamic_modint::mod` in the original ACL.
        ///
        /// # Example
        ///
        /// ```
        /// use ac_library_rs::modint::ModIntBase;
        ///
        /// fn f<Z: ModIntBase>() {
        ///     let _: u32 = Z::modulus();
        /// }
        /// ```
        fn modulus() -> u32;

        /// Constructs a `Self` from a `val < Self::modulus()` without checking it.
        ///
        /// Corresponds to `atcoder::static_modint::raw` and `atcoder::dynamic_modint::raw` in the original ACL.
        ///
        /// # Constraints
        ///
        /// - `val` is less than `Self::modulus()`
        ///
        /// **Note that all operations assume that inner values are smaller than the modulus.**
        /// If `val` is greater than or equal to `Self::modulus()`, the behaviors are not defined.
        ///
        /// ```should_panic
        /// use ac_library_rs::ModInt1000000007 as Mint;
        ///
        /// let x = Mint::raw(1_000_000_007);
        /// let y = x + x;
        /// assert_eq!(0, y.val());
        /// ```
        ///
        /// ```text
        /// thread 'main' panicked at 'assertion failed: `(left == right)`
        ///   left: `0`,
        ///  right: `1000000007`', src/modint.rs:8:1
        /// note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace
        /// ```
        ///
        /// # Example
        ///
        /// ```
        /// use ac_library_rs::modint::ModIntBase;
        ///
        /// fn f<Z: ModIntBase>() -> Z {
        ///     debug_assert!(Z::modulus() >= 100);
        ///
        ///     let mut acc = Z::new(0);
        ///     for i in 0..100 {
        ///         if i % 3 == 0 {
        ///             // I know `i` is smaller than the modulus!
        ///             acc += Z::raw(i);
        ///         }
        ///     }
        ///     acc
        /// }
        /// ```
        fn raw(val: u32) -> Self;

        /// Retruns the representative.
        ///
        /// Corresponds to `atcoder::static_modint::val` and `atcoder::dynamic_modint::val` in the original ACL.
        ///
        /// # Example
        ///
        /// ```
        /// use ac_library_rs::modint::ModIntBase;
        ///
        /// fn f<Z: ModIntBase>(x: Z) {
        ///     let _: u32 = x.val();
        /// }
        /// ```
        fn val(self) -> u32;

        /// Retruns the multiplicative inverse of `self`.
        ///
        /// Corresponds to `atcoder::static_modint::inv` and `atcoder::dynamic_modint::inv` in the original ACL.
        ///
        /// # Panics
        ///
        /// Panics if the multiplicative inverse does not exist.
        ///
        /// # Example
        ///
        /// ```
        /// use ac_library_rs::modint::ModIntBase;
        ///
        /// fn f<Z: ModIntBase>(x: Z) {
        ///     let _: Z = x.inv();
        /// }
        /// ```
        fn inv(self) -> Self;

        /// Creates a new `Self`.
        ///
        /// Takes [any primitive integer].
        ///
        /// # Example
        ///
        /// ```
        /// use ac_library_rs::modint::ModIntBase;
        ///
        /// fn f<Z: ModIntBase>() {
        ///     let _ = Z::new(1u32);
        ///     let _ = Z::new(1usize);
        ///     let _ = Z::new(-1i64);
        /// }
        /// ```
        ///
        /// [any primitive integer]:  ../trait.RemEuclidU32.html
        #[inline]
        fn new<T: RemEuclidU32>(val: T) -> Self {
            Self::raw(val.rem_euclid_u32(Self::modulus()))
        }

        /// Returns `self` to the power of `n`.
        ///
        /// Corresponds to `atcoder::static_modint::pow` and `atcoder::dynamic_modint::pow` in the original ACL.
        ///
        /// # Example
        ///
        /// ```
        /// use ac_library_rs::modint::ModIntBase;
        ///
        /// fn f<Z: ModIntBase>() {
        ///     let _: Z = Z::new(2).pow(3);
        /// }
        /// ```
        #[inline]
        fn pow(self, mut n: u64) -> Self {
            let mut x = self;
            let mut r = Self::raw(1);
            while n > 0 {
                if n & 1 == 1 {
                    r *= x;
                }
                x *= x;
                n >>= 1;
            }
            r
        }
    }

    /// A trait for `{StaticModInt, DynamicModInt, ModIntBase}::new`.
    pub trait RemEuclidU32 {
        /// Calculates `self` _mod_ `modulus` losslessly.
        fn rem_euclid_u32(self, modulus: u32) -> u32;
    }

    macro_rules! impl_rem_euclid_u32_for_small_signed {
    ($($ty:tt),*) => {
        $(
            impl RemEuclidU32 for $ty {
                #[inline]
                fn rem_euclid_u32(self, modulus: u32) -> u32 {
                    (self as i64).rem_euclid(i64::from(modulus)) as _
                }
            }
        )*
    }
}

    impl_rem_euclid_u32_for_small_signed!(i8, i16, i32, i64, isize);

    impl RemEuclidU32 for i128 {
        #[inline]
        fn rem_euclid_u32(self, modulus: u32) -> u32 {
            self.rem_euclid(i128::from(modulus)) as _
        }
    }

    macro_rules! impl_rem_euclid_u32_for_small_unsigned {
    ($($ty:tt),*) => {
        $(
            impl RemEuclidU32 for $ty {
                #[inline]
                fn rem_euclid_u32(self, modulus: u32) -> u32 {
                    self as u32 % modulus
                }
            }
        )*
    }
}

    macro_rules! impl_rem_euclid_u32_for_large_unsigned {
    ($($ty:tt),*) => {
        $(
            impl RemEuclidU32 for $ty {
                #[inline]
                fn rem_euclid_u32(self, modulus: u32) -> u32 {
                    (self % (modulus as $ty)) as _
                }
            }
        )*
    }
}

    impl_rem_euclid_u32_for_small_unsigned!(u8, u16, u32);
    impl_rem_euclid_u32_for_large_unsigned!(u64, u128);

    #[cfg(target_pointer_width = "32")]
    impl_rem_euclid_u32_for_small_unsigned!(usize);

    #[cfg(target_pointer_width = "64")]
    impl_rem_euclid_u32_for_large_unsigned!(usize);

    trait InternalImplementations: ModIntBase {
        #[inline]
        fn inv_for_non_prime_modulus(this: Self) -> Self {
            let (gcd, x) = internal_math::inv_gcd(this.val().into(), Self::modulus().into());
            if gcd != 1 {
                panic!("the multiplicative inverse does not exist");
            }
            Self::new(x)
        }

        #[inline]
        fn default_impl() -> Self {
            Self::raw(0)
        }

        #[inline]
        fn from_str_impl(s: &str) -> Result<Self, Infallible> {
            Ok(s.parse::<i64>()
                .map(Self::new)
                .unwrap_or_else(|_| todo!("parsing as an arbitrary precision integer?")))
        }

        #[inline]
        fn hash_impl(this: &Self, state: &mut impl Hasher) {
            this.val().hash(state)
        }

        #[inline]
        fn display_impl(this: &Self, f: &mut fmt::Formatter) -> fmt::Result {
            fmt::Display::fmt(&this.val(), f)
        }

        #[inline]
        fn debug_impl(this: &Self, f: &mut fmt::Formatter) -> fmt::Result {
            fmt::Debug::fmt(&this.val(), f)
        }

        #[inline]
        fn neg_impl(this: Self) -> Self {
            Self::sub_impl(Self::raw(0), this)
        }

        #[inline]
        fn add_impl(lhs: Self, rhs: Self) -> Self {
            let modulus = Self::modulus();
            let mut val = lhs.val() + rhs.val();
            if val >= modulus {
                val -= modulus;
            }
            Self::raw(val)
        }

        #[inline]
        fn sub_impl(lhs: Self, rhs: Self) -> Self {
            let modulus = Self::modulus();
            let mut val = lhs.val().wrapping_sub(rhs.val());
            if val >= modulus {
                val = val.wrapping_add(modulus)
            }
            Self::raw(val)
        }

        fn mul_impl(lhs: Self, rhs: Self) -> Self;

        #[inline]
        fn div_impl(lhs: Self, rhs: Self) -> Self {
            Self::mul_impl(lhs, rhs.inv())
        }
    }

    impl<M: Modulus> InternalImplementations for StaticModInt<M> {
        #[inline]
        fn mul_impl(lhs: Self, rhs: Self) -> Self {
            Self::raw((u64::from(lhs.val()) * u64::from(rhs.val()) % u64::from(M::VALUE)) as u32)
        }
    }

    impl<I: Id> InternalImplementations for DynamicModInt<I> {
        #[inline]
        fn mul_impl(lhs: Self, rhs: Self) -> Self {
            Self::raw(I::companion_barrett().mul(lhs.val, rhs.val))
        }
    }

    macro_rules! impl_basic_traits {
    () => {};
    (impl <$generic_param:ident : $generic_param_bound:tt> _ for $self:ty; $($rest:tt)*) => {
        impl <$generic_param: $generic_param_bound> Default for $self {
            #[inline]
            fn default() -> Self {
                Self::default_impl()
            }
        }

        impl <$generic_param: $generic_param_bound> FromStr for $self {
            type Err = Infallible;

            #[inline]
            fn from_str(s: &str) -> Result<Self, Infallible> {
                Self::from_str_impl(s)
            }
        }

        impl<$generic_param: $generic_param_bound, V: RemEuclidU32> From<V> for $self {
            #[inline]
            fn from(from: V) -> Self {
                Self::new(from)
            }
        }

        #[allow(clippy::derive_hash_xor_eq)]
        impl<$generic_param: $generic_param_bound> Hash for $self {
            #[inline]
            fn hash<H: Hasher>(&self, state: &mut H) {
                Self::hash_impl(self, state)
            }
        }

        impl<$generic_param: $generic_param_bound> fmt::Display for $self {
            #[inline]
            fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
                Self::display_impl(self, f)
            }
        }

        impl<$generic_param: $generic_param_bound> fmt::Debug for $self {
            #[inline]
            fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
                Self::debug_impl(self, f)
            }
        }

        impl<$generic_param: $generic_param_bound> Neg for $self {
            type Output = $self;

            #[inline]
            fn neg(self) -> $self {
                Self::neg_impl(self)
            }
        }

        impl<$generic_param: $generic_param_bound> Neg for &'_ $self {
            type Output = $self;

            #[inline]
            fn neg(self) -> $self {
                <$self>::neg_impl(*self)
            }
        }

        impl_basic_traits!($($rest)*);
    };
}

    impl_basic_traits! {
        impl <M: Modulus> _ for StaticModInt<M> ;
        impl <I: Id     > _ for DynamicModInt<I>;
    }

    macro_rules! impl_bin_ops {
    () => {};
    (for<$($generic_param:ident : $generic_param_bound:tt),*> <$lhs_ty:ty> ~ <$rhs_ty:ty> -> $output:ty { { $lhs_body:expr } ~ { $rhs_body:expr } } $($rest:tt)*) => {
        impl <$($generic_param: $generic_param_bound),*> Add<$rhs_ty> for $lhs_ty {
            type Output = $output;

            #[inline]
            fn add(self, rhs: $rhs_ty) -> $output {
                <$output>::add_impl(apply($lhs_body, self), apply($rhs_body, rhs))
            }
        }

        impl <$($generic_param: $generic_param_bound),*> Sub<$rhs_ty> for $lhs_ty {
            type Output = $output;

            #[inline]
            fn sub(self, rhs: $rhs_ty) -> $output {
                <$output>::sub_impl(apply($lhs_body, self), apply($rhs_body, rhs))
            }
        }

        impl <$($generic_param: $generic_param_bound),*> Mul<$rhs_ty> for $lhs_ty {
            type Output = $output;

            #[inline]
            fn mul(self, rhs: $rhs_ty) -> $output {
                <$output>::mul_impl(apply($lhs_body, self), apply($rhs_body, rhs))
            }
        }

        impl <$($generic_param: $generic_param_bound),*> Div<$rhs_ty> for $lhs_ty {
            type Output = $output;

            #[inline]
            fn div(self, rhs: $rhs_ty) -> $output {
                <$output>::div_impl(apply($lhs_body, self), apply($rhs_body, rhs))
            }
        }

        impl_bin_ops!($($rest)*);
    };
}

    macro_rules! impl_assign_ops {
    () => {};
    (for<$($generic_param:ident : $generic_param_bound:tt),*> <$lhs_ty:ty> ~= <$rhs_ty:ty> { _ ~= { $rhs_body:expr } } $($rest:tt)*) => {
        impl <$($generic_param: $generic_param_bound),*> AddAssign<$rhs_ty> for $lhs_ty {
            #[inline]
            fn add_assign(&mut self, rhs: $rhs_ty) {
                *self = *self + apply($rhs_body, rhs);
            }
        }

        impl <$($generic_param: $generic_param_bound),*> SubAssign<$rhs_ty> for $lhs_ty {
            #[inline]
            fn sub_assign(&mut self, rhs: $rhs_ty) {
                *self = *self - apply($rhs_body, rhs);
            }
        }

        impl <$($generic_param: $generic_param_bound),*> MulAssign<$rhs_ty> for $lhs_ty {
            #[inline]
            fn mul_assign(&mut self, rhs: $rhs_ty) {
                *self = *self * apply($rhs_body, rhs);
            }
        }

        impl <$($generic_param: $generic_param_bound),*> DivAssign<$rhs_ty> for $lhs_ty {
            #[inline]
            fn div_assign(&mut self, rhs: $rhs_ty) {
                *self = *self / apply($rhs_body, rhs);
            }
        }

        impl_assign_ops!($($rest)*);
    };
}

    #[inline]
    fn apply<F: FnOnce(X) -> O, X, O>(f: F, x: X) -> O {
        f(x)
    }

    impl_bin_ops! {
        for<M: Modulus> <StaticModInt<M>     > ~ <StaticModInt<M>     > -> StaticModInt<M>  { { |x| x  } ~ { |x| x  } }
        for<M: Modulus> <StaticModInt<M>     > ~ <&'_ StaticModInt<M> > -> StaticModInt<M>  { { |x| x  } ~ { |&x| x } }
        for<M: Modulus> <&'_ StaticModInt<M> > ~ <StaticModInt<M>     > -> StaticModInt<M>  { { |&x| x } ~ { |x| x  } }
        for<M: Modulus> <&'_ StaticModInt<M> > ~ <&'_ StaticModInt<M> > -> StaticModInt<M>  { { |&x| x } ~ { |&x| x } }
        for<I: Id     > <DynamicModInt<I>    > ~ <DynamicModInt<I>    > -> DynamicModInt<I> { { |x| x  } ~ { |x| x  } }
        for<I: Id     > <DynamicModInt<I>    > ~ <&'_ DynamicModInt<I>> -> DynamicModInt<I> { { |x| x  } ~ { |&x| x } }
        for<I: Id     > <&'_ DynamicModInt<I>> ~ <DynamicModInt<I>    > -> DynamicModInt<I> { { |&x| x } ~ { |x| x  } }
        for<I: Id     > <&'_ DynamicModInt<I>> ~ <&'_ DynamicModInt<I>> -> DynamicModInt<I> { { |&x| x } ~ { |&x| x } }

        for<M: Modulus, T: RemEuclidU32> <StaticModInt<M>     > ~ <T> -> StaticModInt<M>  { { |x| x  } ~ { StaticModInt::<M>::new } }
        for<I: Id     , T: RemEuclidU32> <DynamicModInt<I>    > ~ <T> -> DynamicModInt<I> { { |x| x  } ~ { DynamicModInt::<I>::new } }
    }

    impl_assign_ops! {
        for<M: Modulus> <StaticModInt<M> > ~= <StaticModInt<M>     > { _ ~= { |x| x  } }
        for<M: Modulus> <StaticModInt<M> > ~= <&'_ StaticModInt<M> > { _ ~= { |&x| x } }
        for<I: Id     > <DynamicModInt<I>> ~= <DynamicModInt<I>    > { _ ~= { |x| x  } }
        for<I: Id     > <DynamicModInt<I>> ~= <&'_ DynamicModInt<I>> { _ ~= { |&x| x } }

        for<M: Modulus, T: RemEuclidU32> <StaticModInt<M> > ~= <T> { _ ~= { StaticModInt::<M>::new } }
        for<I: Id,      T: RemEuclidU32> <DynamicModInt<I>> ~= <T> { _ ~= { DynamicModInt::<I>::new } }
    }

    macro_rules! impl_folding {
    () => {};
    (impl<$generic_param:ident : $generic_param_bound:tt> $trait:ident<_> for $self:ty { fn $method:ident(_) -> _ { _($unit:expr, $op:expr) } } $($rest:tt)*) => {
        impl<$generic_param: $generic_param_bound> $trait<Self> for $self {
            #[inline]
            fn $method<S>(iter: S) -> Self
            where
                S: Iterator<Item = Self>,
            {
                iter.fold($unit, $op)
            }
        }

        impl<'a, $generic_param: $generic_param_bound> $trait<&'a Self> for $self {
            #[inline]
            fn $method<S>(iter: S) -> Self
            where
                S: Iterator<Item = &'a Self>,
            {
                iter.fold($unit, $op)
            }
        }

        impl_folding!($($rest)*);
    };
}

    impl_folding! {
        impl<M: Modulus> Sum<_>     for StaticModInt<M>  { fn sum(_)     -> _ { _(Self::raw(0), Add::add) } }
        impl<M: Modulus> Product<_> for StaticModInt<M>  { fn product(_) -> _ { _(Self::raw(1), Mul::mul) } }
        impl<I: Id     > Sum<_>     for DynamicModInt<I> { fn sum(_)     -> _ { _(Self::raw(0), Add::add) } }
        impl<I: Id     > Product<_> for DynamicModInt<I> { fn product(_) -> _ { _(Self::raw(1), Mul::mul) } }
    }
}
pub mod scc {
    use crate::internal_scc;

    pub struct SccGraph {
        internal: internal_scc::SccGraph,
    }

    impl SccGraph {
        pub fn new(n: usize) -> Self {
            SccGraph {
                internal: internal_scc::SccGraph::new(n),
            }
        }

        pub fn add_edge(&mut self, from: usize, to: usize) {
            let n = self.internal.num_vertices();
            assert!(from < n);
            assert!(to < n);
            self.internal.add_edge(from, to);
        }

        pub fn scc(&self) -> Vec<Vec<usize>> {
            self.internal.scc()
        }
    }
}
pub mod segtree {
    use crate::internal_bit::ceil_pow2;
    use crate::internal_type_traits::{BoundedAbove, BoundedBelow, One, Zero};
    use std::cmp::{max, min};
    use std::convert::Infallible;
    use std::marker::PhantomData;
    use std::ops::{Add, Mul};

    // TODO Should I split monoid-related traits to another module?
    pub trait Monoid {
        type S: Clone;
        fn identity() -> Self::S;
        fn binary_operation(a: &Self::S, b: &Self::S) -> Self::S;
    }

    pub struct Max<S>(Infallible, PhantomData<fn() -> S>);
    impl<S> Monoid for Max<S>
    where
        S: Copy + Ord + BoundedBelow,
    {
        type S = S;
        fn identity() -> Self::S {
            S::min_value()
        }
        fn binary_operation(a: &Self::S, b: &Self::S) -> Self::S {
            max(*a, *b)
        }
    }

    pub struct Min<S>(Infallible, PhantomData<fn() -> S>);
    impl<S> Monoid for Min<S>
    where
        S: Copy + Ord + BoundedAbove,
    {
        type S = S;
        fn identity() -> Self::S {
            S::max_value()
        }
        fn binary_operation(a: &Self::S, b: &Self::S) -> Self::S {
            min(*a, *b)
        }
    }

    pub struct Additive<S>(Infallible, PhantomData<fn() -> S>);
    impl<S> Monoid for Additive<S>
    where
        S: Copy + Add<Output = S> + Zero,
    {
        type S = S;
        fn identity() -> Self::S {
            S::zero()
        }
        fn binary_operation(a: &Self::S, b: &Self::S) -> Self::S {
            *a + *b
        }
    }

    pub struct Multiplicative<S>(Infallible, PhantomData<fn() -> S>);
    impl<S> Monoid for Multiplicative<S>
    where
        S: Copy + Mul<Output = S> + One,
    {
        type S = S;
        fn identity() -> Self::S {
            S::one()
        }
        fn binary_operation(a: &Self::S, b: &Self::S) -> Self::S {
            *a * *b
        }
    }

    impl<M: Monoid> Default for Segtree<M> {
        fn default() -> Self {
            Segtree::new(0)
        }
    }
    impl<M: Monoid> Segtree<M> {
        pub fn new(n: usize) -> Segtree<M> {
            vec![M::identity(); n].into()
        }
    }
    impl<M: Monoid> From<Vec<M::S>> for Segtree<M> {
        fn from(v: Vec<M::S>) -> Self {
            let n = v.len();
            let log = ceil_pow2(n as u32) as usize;
            let size = 1 << log;
            let mut d = vec![M::identity(); 2 * size];
            d[size..(size + n)].clone_from_slice(&v);
            let mut ret = Segtree { n, size, log, d };
            for i in (1..size).rev() {
                ret.update(i);
            }
            ret
        }
    }
    impl<M: Monoid> Segtree<M> {
        pub fn set(&mut self, mut p: usize, x: M::S) {
            assert!(p < self.n);
            p += self.size;
            self.d[p] = x;
            for i in 1..=self.log {
                self.update(p >> i);
            }
        }

        pub fn get(&self, p: usize) -> M::S {
            assert!(p < self.n);
            self.d[p + self.size].clone()
        }

        pub fn prod(&self, mut l: usize, mut r: usize) -> M::S {
            assert!(l <= r && r <= self.n);
            let mut sml = M::identity();
            let mut smr = M::identity();
            l += self.size;
            r += self.size;

            while l < r {
                if l & 1 != 0 {
                    sml = M::binary_operation(&sml, &self.d[l]);
                    l += 1;
                }
                if r & 1 != 0 {
                    r -= 1;
                    smr = M::binary_operation(&self.d[r], &smr);
                }
                l >>= 1;
                r >>= 1;
            }

            M::binary_operation(&sml, &smr)
        }

        pub fn all_prod(&self) -> M::S {
            self.d[1].clone()
        }

        pub fn max_right<F>(&self, mut l: usize, f: F) -> usize
        where
            F: Fn(&M::S) -> bool,
        {
            assert!(l <= self.n);
            assert!(f(&M::identity()));
            if l == self.n {
                return self.n;
            }
            l += self.size;
            let mut sm = M::identity();
            while {
                // do
                while l % 2 == 0 {
                    l >>= 1;
                }
                if !f(&M::binary_operation(&sm, &self.d[l])) {
                    while l < self.size {
                        l *= 2;
                        let res = M::binary_operation(&sm, &self.d[l]);
                        if f(&res) {
                            sm = res;
                            l += 1;
                        }
                    }
                    return l - self.size;
                }
                sm = M::binary_operation(&sm, &self.d[l]);
                l += 1;
                // while
                {
                    let l = l as isize;
                    (l & -l) != l
                }
            } {}
            self.n
        }

        pub fn min_left<F>(&self, mut r: usize, f: F) -> usize
        where
            F: Fn(&M::S) -> bool,
        {
            assert!(r <= self.n);
            assert!(f(&M::identity()));
            if r == 0 {
                return 0;
            }
            r += self.size;
            let mut sm = M::identity();
            while {
                // do
                r -= 1;
                while r > 1 && r % 2 == 1 {
                    r >>= 1;
                }
                if !f(&M::binary_operation(&self.d[r], &sm)) {
                    while r < self.size {
                        r = 2 * r + 1;
                        let res = M::binary_operation(&self.d[r], &sm);
                        if f(&res) {
                            sm = res;
                            r -= 1;
                        }
                    }
                    return r + 1 - self.size;
                }
                sm = M::binary_operation(&self.d[r], &sm);
                // while
                {
                    let r = r as isize;
                    (r & -r) != r
                }
            } {}
            0
        }

        fn update(&mut self, k: usize) {
            self.d[k] = M::binary_operation(&self.d[2 * k], &self.d[2 * k + 1]);
        }
    }

    // Maybe we can use this someday
    // ```
    // for i in 0..=self.log {
    //     for j in 0..1 << i {
    //         print!("{}\t", self.d[(1 << i) + j]);
    //     }
    //     println!();
    // }
    // ```

    pub struct Segtree<M>
    where
        M: Monoid,
    {
        // variable name is _n in original library
        n: usize,
        size: usize,
        log: usize,
        d: Vec<M::S>,
    }
}
pub mod string {
    #![allow(clippy::many_single_char_names)]

    fn sa_naive<T: Ord>(s: &[T]) -> Vec<usize> {
        let n = s.len();
        let mut sa: Vec<usize> = (0..n).collect();
        sa.sort_by(|&(mut l), &(mut r)| {
            if l == r {
                return std::cmp::Ordering::Equal;
            }
            while l < n && r < n {
                if s[l] != s[r] {
                    return s[l].cmp(&s[r]);
                }
                l += 1;
                r += 1;
            }
            if l == n {
                std::cmp::Ordering::Less
            } else {
                std::cmp::Ordering::Greater
            }
        });
        sa
    }

    fn sa_doubling(s: &[i32]) -> Vec<usize> {
        let n = s.len();
        let mut sa: Vec<usize> = (0..n).collect();
        let mut rnk: Vec<i32> = s.to_vec();
        let mut tmp = vec![0; n];
        let mut k = 1;
        while k < n {
            let cmp = |&x: &usize, &y: &usize| {
                if rnk[x] != rnk[y] {
                    return rnk[x].cmp(&rnk[y]);
                }
                let rx = if x + k < n { rnk[x + k] } else { -1 };
                let ry = if y + k < n { rnk[y + k] } else { -1 };
                rx.cmp(&ry)
            };
            sa.sort_by(cmp);
            tmp[sa[0]] = 0;
            for i in 1..n {
                tmp[sa[i]] = tmp[sa[i - 1]]
                    + if cmp(&sa[i - 1], &sa[i]) == std::cmp::Ordering::Less {
                        1
                    } else {
                        0
                    };
            }
            std::mem::swap(&mut tmp, &mut rnk);
            k *= 2;
        }
        sa
    }

    trait Threshold {
        fn threshold_naive() -> usize;
        fn threshold_doubling() -> usize;
    }

    enum DefaultThreshold {}
    impl Threshold for DefaultThreshold {
        fn threshold_naive() -> usize {
            10
        }
        fn threshold_doubling() -> usize {
            40
        }
    }

    #[allow(clippy::cognitive_complexity)]
    fn sa_is<T: Threshold>(s: &[usize], upper: usize) -> Vec<usize> {
        let n = s.len();
        match n {
            0 => return vec![],
            1 => return vec![0],
            2 => return if s[0] < s[1] { vec![0, 1] } else { vec![1, 0] },
            _ => (),
        }
        if n < T::threshold_naive() {
            return sa_naive(s);
        }
        if n < T::threshold_doubling() {
            let s: Vec<i32> = s.iter().map(|&x| x as i32).collect();
            return sa_doubling(&s);
        }
        let mut sa = vec![0; n];
        let mut ls = vec![false; n];
        for i in (0..n - 1).rev() {
            ls[i] = if s[i] == s[i + 1] {
                ls[i + 1]
            } else {
                s[i] < s[i + 1]
            };
        }
        let mut sum_l = vec![0; upper + 1];
        let mut sum_s = vec![0; upper + 1];
        for i in 0..n {
            if !ls[i] {
                sum_s[s[i]] += 1;
            } else {
                sum_l[s[i] + 1] += 1;
            }
        }
        for i in 0..=upper {
            sum_s[i] += sum_l[i];
            if i < upper {
                sum_l[i + 1] += sum_s[i];
            }
        }

        // sa's origin is 1.
        let induce = |sa: &mut [usize], lms: &[usize]| {
            for elem in sa.iter_mut() {
                *elem = 0;
            }
            let mut buf = sum_s.clone();
            for &d in lms {
                if d == n {
                    continue;
                }
                let old = buf[s[d]];
                buf[s[d]] += 1;
                sa[old] = d + 1;
            }
            buf.copy_from_slice(&sum_l);
            let old = buf[s[n - 1]];
            buf[s[n - 1]] += 1;
            sa[old] = n;
            for i in 0..n {
                let v = sa[i];
                if v >= 2 && !ls[v - 2] {
                    let old = buf[s[v - 2]];
                    buf[s[v - 2]] += 1;
                    sa[old] = v - 1;
                }
            }
            buf.copy_from_slice(&sum_l);
            for i in (0..n).rev() {
                let v = sa[i];
                if v >= 2 && ls[v - 2] {
                    buf[s[v - 2] + 1] -= 1;
                    sa[buf[s[v - 2] + 1]] = v - 1;
                }
            }
        };
        // origin: 1
        let mut lms_map = vec![0; n + 1];
        let mut m = 0;
        for i in 1..n {
            if !ls[i - 1] && ls[i] {
                lms_map[i] = m + 1;
                m += 1;
            }
        }
        let mut lms = Vec::with_capacity(m);
        for i in 1..n {
            if !ls[i - 1] && ls[i] {
                lms.push(i);
            }
        }
        assert_eq!(lms.len(), m);
        induce(&mut sa, &lms);

        if m > 0 {
            let mut sorted_lms = Vec::with_capacity(m);
            for &v in &sa {
                if lms_map[v - 1] != 0 {
                    sorted_lms.push(v - 1);
                }
            }
            let mut rec_s = vec![0; m];
            let mut rec_upper = 0;
            rec_s[lms_map[sorted_lms[0]] - 1] = 0;
            for i in 1..m {
                let mut l = sorted_lms[i - 1];
                let mut r = sorted_lms[i];
                let end_l = if lms_map[l] < m { lms[lms_map[l]] } else { n };
                let end_r = if lms_map[r] < m { lms[lms_map[r]] } else { n };
                let same = if end_l - l != end_r - r {
                    false
                } else {
                    while l < end_l {
                        if s[l] != s[r] {
                            break;
                        }
                        l += 1;
                        r += 1;
                    }
                    l != n && s[l] == s[r]
                };
                if !same {
                    rec_upper += 1;
                }
                rec_s[lms_map[sorted_lms[i]] - 1] = rec_upper;
            }

            let rec_sa = sa_is::<T>(&rec_s, rec_upper);
            for i in 0..m {
                sorted_lms[i] = lms[rec_sa[i]];
            }
            induce(&mut sa, &mut sorted_lms);
        }
        for elem in sa.iter_mut() {
            *elem -= 1;
        }
        sa
    }

    fn sa_is_i32<T: Threshold>(s: &[i32], upper: i32) -> Vec<usize> {
        let s: Vec<usize> = s.iter().map(|&x| x as usize).collect();
        sa_is::<T>(&s, upper as usize)
    }

    pub fn suffix_array_manual(s: &[i32], upper: i32) -> Vec<usize> {
        assert!(upper >= 0);
        for &elem in s {
            assert!(0 <= elem && elem <= upper);
        }
        sa_is_i32::<DefaultThreshold>(s, upper)
    }

    pub fn suffix_array_arbitrary<T: Ord>(s: &[T]) -> Vec<usize> {
        let n = s.len();
        let mut idx: Vec<usize> = (0..n).collect();
        idx.sort_by_key(|&i| &s[i]);
        let mut s2 = vec![0; n];
        let mut now = 0;
        for i in 0..n {
            if i > 0 && s[idx[i - 1]] != s[idx[i]] {
                now += 1;
            }
            s2[idx[i]] = now;
        }
        sa_is_i32::<DefaultThreshold>(&s2, now)
    }

    pub fn suffix_array(s: &str) -> Vec<usize> {
        let s2: Vec<usize> = s.bytes().map(|x| x as usize).collect();
        sa_is::<DefaultThreshold>(&s2, 255)
    }

    // Reference:
    // T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,
    // Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its
    // Applications
    pub fn lcp_array_arbitrary<T: Ord>(s: &[T], sa: &[usize]) -> Vec<usize> {
        let n = s.len();
        assert!(n >= 1);
        let mut rnk = vec![0; n];
        for i in 0..n {
            rnk[sa[i]] = i;
        }
        let mut lcp = vec![0; n - 1];
        let mut h = 0;
        for i in 0..n - 1 {
            if h > 0 {
                h -= 1;
            }
            if rnk[i] == 0 {
                continue;
            }
            let j = sa[rnk[i] - 1];
            while j + h < n && i + h < n {
                if s[j + h] != s[i + h] {
                    break;
                }
                h += 1;
            }
            lcp[rnk[i] - 1] = h;
        }
        lcp
    }

    pub fn lcp_array(s: &str, sa: &[usize]) -> Vec<usize> {
        let s: &[u8] = s.as_bytes();
        lcp_array_arbitrary(s, sa)
    }

    // Reference:
    // D. Gusfield,
    // Algorithms on Strings, Trees, and Sequences: Computer Science and
    // Computational Biology
    pub fn z_algorithm_arbitrary<T: Ord>(s: &[T]) -> Vec<usize> {
        let n = s.len();
        if n == 0 {
            return vec![];
        }
        let mut z = vec![0; n];
        z[0] = 0;
        let mut j = 0;
        for i in 1..n {
            let mut k = if j + z[j] <= i {
                0
            } else {
                std::cmp::min(j + z[j] - i, z[i - j])
            };
            while i + k < n && s[k] == s[i + k] {
                k += 1;
            }
            z[i] = k;
            if j + z[j] < i + z[i] {
                j = i;
            }
        }
        z[0] = n;
        z
    }

    pub fn z_algorithm(s: &str) -> Vec<usize> {
        let s: &[u8] = s.as_bytes();
        z_algorithm_arbitrary(s)
    }
}
pub mod twosat {
    use crate::internal_scc;

    pub struct TwoSat {
        n: usize,
        scc: internal_scc::SccGraph,
        answer: Vec<bool>,
    }
    impl TwoSat {
        pub fn new(n: usize) -> Self {
            TwoSat {
                n,
                answer: vec![false; n],
                scc: internal_scc::SccGraph::new(2 * n),
            }
        }
        pub fn add_clause(&mut self, i: usize, f: bool, j: usize, g: bool) {
            assert!(i < self.n && j < self.n);
            self.scc.add_edge(2 * i + !f as usize, 2 * j + g as usize);
            self.scc.add_edge(2 * j + !g as usize, 2 * i + f as usize);
        }
        pub fn satisfiable(&mut self) -> bool {
            let id = self.scc.scc_ids().1;
            for i in 0..self.n {
                if id[2 * i] == id[2 * i + 1] {
                    return false;
                }
                self.answer[i] = id[2 * i] < id[2 * i + 1];
            }
            true
        }
        pub fn answer(&self) -> &[bool] {
            &self.answer
        }
    }
}
use std::collections::BTreeMap;

pub use combination::*;
pub use convolution::*;
pub use dsu::*;
pub use fenwicktree::*;
pub use lazysegtree::*;
pub use lca::*;
pub use math::*;
pub use maxflow::*;
pub use mincostflow::*;
pub use modint::*;
pub use scc::*;
pub use segtree::*;
pub use string::*;
pub use twosat::*;
