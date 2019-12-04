pub struct UnionFind {
    par: Vec<usize>,
    rnk: Vec<usize>,
    cnt: Vec<usize>,
}

impl UnionFind {
    pub fn new(n: usize) -> Self {
        let par: Vec<usize> = (0..n).collect();
        let rnk: Vec<usize> = vec![0; n];
        let cnt: Vec<usize> = vec![1; n];
        UnionFind {
            par: par,
            rnk: rnk,
            cnt: cnt,
        }
    }

    pub fn root(&mut self, i: usize) -> usize {
        if self.par[i] != i {
            let p = self.par[i];
            self.par[i] = self.root(p);
        }
        self.par[i]
    }
    pub fn unite(&mut self, i: usize, j: usize) {
        let ri = self.root(i);
        let rj = self.root(j);
        if ri == rj { return };

        if self.rnk[ri] == self.rnk[rj] {
            self.cnt[rj] += self.cnt[ri];
            self.par[ri] = rj;
            self.rnk[rj] += 1;
        } else if self.rnk[ri] < self.rnk[rj] {
            self.cnt[rj] += self.cnt[ri];
            self.par[ri] = rj;
        } else {
            self.cnt[ri] += self.cnt[rj];
            self.par[rj] = ri;
        }
    }
    pub fn same(&mut self, i: usize, j: usize) -> bool {
        self.root(i) == self.root(j)
    }
    pub fn count(&mut self, i: usize) -> usize {
        let r = self.root(i);
        self.cnt[r]
    }
}


#[cfg(test)]
mod union_find_tests {
    use super::*;

    #[test]
    fn test_new() {
        let n = 10;
        let uf = UnionFind::new(n);
        assert_eq!(uf.par.len(), n);
        assert_eq!(uf.rnk.len(), n);
        assert_eq!(uf.cnt.len(), n);
    }

    #[test]
    fn test_root() {
        let n = 10;
        let mut uf = UnionFind::new(n);
        for i in 0..n {
            assert_eq!(uf.root(i), i);
        }
    }

    #[test]
    fn test_unite() {
        let n = 10;
        let mut uf = UnionFind::new(n);
        uf.unite(0, 3);
        uf.unite(0, 9);
        uf.unite(1, 2);
        uf.unite(4, 9);
        uf.unite(5, 1);
        assert_eq!(uf.root(0), uf.root(3));
        assert_eq!(uf.root(3), uf.root(9));
        assert_eq!(uf.root(1), uf.root(5));
        assert_eq!(uf.root(0), uf.root(4));
        assert!(uf.root(0) != uf.root(1));
        assert!(uf.root(2) != uf.root(3));
        assert!(uf.root(5) != uf.root(9));
    }

    #[test]
    fn test_count() {
        let n = 10;
        let mut uf = UnionFind::new(n);
        uf.unite(0, 3);
        uf.unite(0, 9);
        uf.unite(1, 2);
        uf.unite(4, 9);
        uf.unite(5, 1);
        assert_eq!(uf.count(0), 4);
        assert_eq!(uf.count(3), 4);
        assert_eq!(uf.count(1), 3);
        assert_eq!(uf.count(6), 1);
    }
}
