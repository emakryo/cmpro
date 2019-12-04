pub struct SegmentTree<T, E, M, A, P> {
    n: usize, height: usize, data: Vec<T>, lazy: Vec<E>, data_default: T, lazy_default: E,
    merge: M, apply: A, propagate: P,
}

impl<T, E, M, A, P> SegmentTree<T, E, M, A, P>
where T: Copy + Eq, E: Copy + Eq, M: Fn(T, T) -> T, A: Fn(T, E) -> T, P: Fn(E, E) -> E,
{
    pub fn new(n_: usize, data_default: T, lazy_default: E,
               merge: M, apply: A, propagate: P) -> Self {
        let mut n = 1;
        let mut height = 0;
        while n < n_ { n <<= 1; height += 1; }
        SegmentTree {
            n: n, height: height, data: vec![data_default; 2*n], lazy: vec![lazy_default; 2*n],
            data_default: data_default, lazy_default: lazy_default,
            merge: merge, apply: apply, propagate: propagate,
        }
    }
    pub fn from_vec(data: &[T], data_default: T, lazy_default: E,
                    merge: M, apply: A, propagate: P) -> Self {
        let n = data.len();
        let mut st = Self::new(n, data_default, lazy_default, merge, apply, propagate);
        for i in 0..n { st.data[st.n+i] = data[i]; }
        for i in (0..st.n).rev() { st.data[i] = (st.merge)(st.data[i<<1], st.data[(i<<1)|1]); }
        st
    }
    fn reflect(&mut self, k: usize) -> T {
        if self.lazy[k] == self.lazy_default {
            self.data[k]
        } else {
            (self.apply)(self.data[k], self.lazy[k])
        }
    }
    fn eval(&mut self, k: usize) {
        if self.lazy[k] == self.lazy_default { return; }
        self.lazy[k<<1] = (self.propagate)(self.lazy[k<<1], self.lazy[k]);
        self.lazy[(k<<1)|1] = (self.propagate)(self.lazy[(k<<1)|1], self.lazy[k]);
        self.data[k] = self.reflect(k);
        self.lazy[k] = self.lazy_default;
    }
    fn thrust(&mut self, k: usize) {
        for i in (1..(self.height+1)).rev() { self.eval(k>>i); }
    }
    fn recalc(&mut self, k: usize) {
        let mut k = k;
        while k > 0 {
            let x = self.reflect(k<<1);
            let y = self.reflect((k<<1)|1);
            self.data[k] = (self.merge)(x, y);
            k >>= 1;
        }
    }
    pub fn update(&mut self, a: usize, b: usize, x: E) {
        let a = a + self.n;
        self.thrust(a);
        let b = b + self.n - 1;
        self.thrust(b);
        let (mut l, mut r) = (a, b + 1);
        while l < r {
            if l & 1 > 0 { self.lazy[l] = (self.propagate)(self.lazy[l], x); l += 1; }
            if r & 1 > 0 { r -= 1; self.lazy[r] = (self.propagate)(self.lazy[r], x); }
            l >>= 1; r >>= 1;
        }
        self.recalc(a); self.recalc(b);
    }
    pub fn set(&mut self, a: usize, x: T) {
        let a = self.n + a;
        self.thrust(a);
        self.data[a] = x;
        self.lazy[a] = self.lazy_default;
        self.recalc(a);
    }
    pub fn query(&mut self, a: usize, b: usize) -> T {
        let a = a + self.n;
        let b = b + self.n - 1;
        self.thrust(a); self.thrust(b);
        let mut vl = self.data_default;
        let mut vr = self.data_default;
        let (mut l, mut r) = (a, b + 1);
        while l < r {
            if l & 1 > 0 { let x = self.reflect(l); vl = (self.merge)(vl, x); l += 1; }
            if r & 1 > 0 { r -= 1; let x = self.reflect(r); vr = (self.merge)(x, vr); }
            l >>= 1; r >>= 1;
        }
        (self.merge)(vl, vr)
    }
}

#[cfg(test)]
mod segment_tree_tests {
    #[test]
    fn test_new() {}
}
