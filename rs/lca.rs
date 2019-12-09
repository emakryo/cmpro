use std::ops::{Add, Sub};
use std::mem;

pub struct LowestCommonAncestor<T> {
    pub size: usize, pub root: usize,
    ancestors: Vec<Vec<usize>>, depths: Vec<usize>, distances: Vec<Option<T>>,
}

impl<T> LowestCommonAncestor<T> where T: Copy + Add<Output=T> + Sub<Output=T> + From<usize> {
    /// create LCA instance from tree graph, panic if given graph is not a tree
    pub fn from_tree(root: usize, tree: &[Vec<(usize, T)>]) -> Self {
        let size = tree.len();
        let log_size = (64 - (size as u64).leading_zeros()) as usize;
        let ancestors = (0..size).map(|_| vec![0; log_size]).collect();
        let mut lca = LowestCommonAncestor {
            size: size, root: root, 
            ancestors: ancestors, depths: vec![0; size], distances: vec![None; size],
        };
        lca.dfs(root, None, From::from(0), tree);
        for k in 1..log_size { for u in 0..size {
            if lca.distances[u].is_none() { continue; }
            lca.ancestors[u][k] = lca.ancestors[lca.ancestors[u][k-1]][k-1];
        } }
        lca
    }
    fn dfs(&mut self, u: usize, p: Option<usize>, dist: T, tree: &[Vec<(usize, T)>]) {
        if let Some(p) = p {
            self.ancestors[u][0] = p;
            self.depths[u] = 1 + self.depths[p];
        } else {
            self.ancestors[u][0] = u;
            self.depths[u] = 0;
        }
        if self.distances[u].is_some() {
            panic!("Given graph is not a tree");
        }
        self.distances[u] = Some(dist.clone());
        for &(v, x) in tree[u].iter() {
            if p == Some(v) { continue; }
            self.dfs(v, Some(u), dist+x, tree);
        }
    }
    /// return lowest common ancestors if a and b are connected, otherwise, None
    pub fn get(&self, a: usize, b: usize) -> Option<usize> {
        println!("{} {:?}",a, self.ancestors[a]);
        println!("{} {:?}",b, self.ancestors[b]);
        if self.distances[a].is_none() || self.distances[b].is_none() { return None; }
        let mut a = a; let mut b = b;
        if self.depths[a] < self.depths[b] { mem::swap(&mut a, &mut b); }
        let gap = self.depths[a] - self.depths[b]; let log_size = self.ancestors[0].len();
        for k in 0..log_size { if (gap & (1 << k)) > 0 { a = self.ancestors[a][k]; } }
        assert_eq!(self.depths[a], self.depths[b]);
        if a == b { return Some(a); }
        for k in (0..log_size).rev() { if self.ancestors[a][k] != self.ancestors[b][k] {
                a = self.ancestors[a][k]; b = self.ancestors[b][k];
        } }
        assert_eq!(self.ancestors[a][0], self.ancestors[b][0]);
        Some(self.ancestors[a][0])
    }
    /// return distance between a and b if connected, otherwise, None
    pub fn distance(&self, a: usize, b: usize) -> Option<T> {
        match (self.distances[a], self.distances[b], self.get(a, b)) {
            (Some(da), Some(db), Some(u)) => Some(da + db - self.distances[u].unwrap()),
            _ => None,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_from_tree() {
        let tree = vec![vec![(1, 1)], vec![(0, 1)]];
        let lca = LowestCommonAncestor::from_tree(0, &tree);
        let _ = lca.get(0, 1);
        let _ = lca.distance(0, 1);
    }

    #[test]
    fn test_simple() {
        // homogeneous weights
        //      2
        //     /  \
        //    1    3
        //   / \    \
        //  0   5    4
        //     / \
        //    6   7
        //         \
        //          8
        let tree = vec![
            vec![(1, 1)],
            vec![(0, 1), (2, 1), (5, 1)],
            vec![(1, 1), (3, 1)],
            vec![(2, 1), (4, 1)],
            vec![(3, 1)],
            vec![(1, 1), (6, 1), (7, 1)],
            vec![(5, 1)],
            vec![(5, 1), (8, 1)],
            vec![(7, 1)],
        ];
        let lca = LowestCommonAncestor::from_tree(2, &tree);
        assert_eq!(lca.get(0, 1).unwrap(), 1);
        assert_eq!(lca.get(0, 2).unwrap(), 2);
        assert_eq!(lca.get(0, 3).unwrap(), 2);
        assert_eq!(lca.get(0, 5).unwrap(), 1);
        assert_eq!(lca.get(0, 8).unwrap(), 1);
        assert_eq!(lca.get(1, 0).unwrap(), 1);
        assert_eq!(lca.get(1, 2).unwrap(), 2);
        assert_eq!(lca.get(1, 4).unwrap(), 2);
        assert_eq!(lca.get(1, 8).unwrap(), 1);
        assert_eq!(lca.get(6, 8).unwrap(), 5);
    }
}
