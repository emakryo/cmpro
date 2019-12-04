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
    pub fn from_slice(data: &[T], data_default: T, lazy_default: E,
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
        while { k >>= 1; k > 0 } {
            let x = self.reflect(k<<1);
            let y = self.reflect((k<<1)|1);
            self.data[k] = (self.merge)(x, y);
        }
    }
    /// update [a, b) by x
    pub fn update(&mut self, a: usize, b: usize, x: E) {
        let a = a + self.n; self.thrust(a);
        let b = b + self.n - 1; self.thrust(b);
        let (mut l, mut r) = (a, b + 1);
        while l < r {
            if l & 1 > 0 { self.lazy[l] = (self.propagate)(self.lazy[l], x); l += 1; }
            if r & 1 > 0 { r -= 1; self.lazy[r] = (self.propagate)(self.lazy[r], x); }
            l >>= 1; r >>= 1;
        }
        self.recalc(a); self.recalc(b);
    }
    /// set value x at index a
    pub fn set(&mut self, a: usize, x: T) {
        let a = self.n + a;
        self.thrust(a);
        self.data[a] = x;
        self.lazy[a] = self.lazy_default;
        self.recalc(a);
    }
    /// query between [a, b)
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
mod tests {
    use super::*;
    use std::cmp::min;
    #[test]
    fn test_new() {
        let m = |x, y| min(x, y);
        let a = |x, _| x;
        let p = |_, _| 0;
        let _st: SegmentTree<i64, i64, _, _, _> = SegmentTree::new(
            10, i64::max_value(), 0, m, a, p);
    }

    #[test]
    fn test_min() {
        let m = |x, y| min(x, y);
        let a = |x, _| x;
        let p = |_, _| 0;
        let v = vec![2, 3, 0, 5, 2, 9, 4, 3, 2];
        let mut st = SegmentTree::from_slice(&v, i64::max_value(), 0, m, a, p);
        assert_eq!(st.query(0, 1), 2);
        assert_eq!(st.query(0, 2), 2);
        assert_eq!(st.query(0, 3), 0);
        assert_eq!(st.query(0, 4), 0);
        assert_eq!(st.query(0, 5), 0);
        assert_eq!(st.query(2, 5), 0);
        assert_eq!(st.query(3, 5), 2);
        for (i, x) in v.iter().enumerate() {
            assert_eq!(st.query(i, i+1), *x);
        }

        st.set(2, 7);
        assert_eq!(st.query(0, 1), 2);
        assert_eq!(st.query(0, 2), 2);
        assert_eq!(st.query(0, 3), 2);
        assert_eq!(st.query(0, 4), 2);
        assert_eq!(st.query(1, 4), 3);
        assert_eq!(st.query(2, 4), 5);
        for (i, x) in v.iter().enumerate() {
            let x = if i == 2 { 7 } else { *x };
            assert_eq!(st.query(i, i+1), x);
        }
    }

    #[test]
    fn test_min_add() {
        let m = |x, y| min(x, y);
        let a = |x, t| x + t;
        let p = |t, s| t + s;
        let v = vec![2, 3, 0, 5, 2, 9, 4, 3, 2];
        let mut st = SegmentTree::from_slice(&v, i64::max_value(), 0, m, a, p);
        assert_eq!(st.query(0, 1), 2);
        assert_eq!(st.query(0, 2), 2);
        assert_eq!(st.query(0, 3), 0);
        assert_eq!(st.query(0, 4), 0);
        assert_eq!(st.query(0, 5), 0);
        assert_eq!(st.query(2, 5), 0);
        assert_eq!(st.query(3, 5), 2);
        for (i, x) in v.iter().enumerate() {
            assert_eq!(st.query(i, i+1), *x);
        }

        st.set(2, 7);
        let v = vec![2, 3, 7, 5, 2, 9, 4, 3, 2];
        assert_eq!(st.query(0, 1), 2);
        assert_eq!(st.query(0, 2), 2);
        assert_eq!(st.query(0, 3), 2);
        assert_eq!(st.query(0, 4), 2);
        assert_eq!(st.query(1, 4), 3);
        assert_eq!(st.query(2, 4), 5);
        for (i, x) in v.iter().enumerate() {
            assert_eq!(st.query(i, i+1), *x);
        }

        st.update(2, 5, 4);
        let v = vec![2, 3, 11, 9, 6, 9, 4, 3, 2];
        assert_eq!(st.query(0, 2), 2);
        assert_eq!(st.query(0, 3), 2);
        assert_eq!(st.query(0, 4), 2);
        assert_eq!(st.query(1, 4), 3);
        assert_eq!(st.query(2, 4), 9);
        assert_eq!(st.query(2, 5), 6);
        assert_eq!(st.query(2, 7), 4);
        assert_eq!(st.query(0, 4), 2);
        for (i, x) in v.iter().enumerate() {
            assert_eq!(st.query(i, i+1), *x);
        }
    }
}
