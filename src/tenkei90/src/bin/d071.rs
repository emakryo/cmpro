use std::collections::VecDeque;

use proconio::marker::Usize1;

fn main() {
    proconio::input! {
        (n, m, k): (usize, usize, usize),
        xs: [(Usize1, Usize1); m],
    }

    let mut g = vec![vec![]; n];
    let mut n_in = vec![0; n];
    let mut n_out = vec![0; n];

    for &(a, b) in &xs {
        g[a].push(b);
        n_in[b] += 1;
        n_out[a] += 1;
    }

    let mut vis = vec![false; n];
    let mut active = vec![false; n];
    for i in 0..n {
        if vis[i] { continue }
        if !dfs0(i, &mut vis, &mut active, &g) {
            println!("-1");
            return;
        }
    }

    let mut que = VecDeque::new();
    for i in 0..n {
        if n_in[i] == 0 {
            que.push_back(i);
        }
    }

    let mut ans = vec![];
    let mut xs = vec![];
    let mut used = vec![false; n];

    dfs(&mut que, &mut xs, &mut used, &mut n_in,&mut ans, &g, k);

    if ans.len() < k {
        println!("-1");
        return;
    }
    
    for xs in ans {
        let xs: Vec<_> = xs.into_iter().map(|x| (x+1).to_string()).collect();
        println!("{}", xs.join(" "));
    }

}

fn dfs0(u: usize, vis: &mut Vec<bool>, active: &mut Vec<bool>, g: &Vec<Vec<usize>>) -> bool {
    vis[u] = true;
    active[u] = true;
    for &v in &g[u] {
        if active[v] {
            return false;
        }
        if vis[v] {
            continue;
        }

        if !dfs0(v, vis, active, g) {
            return false;
        }
    }
    active[u] = false;
    return true;
}

fn dfs(que: &mut VecDeque<usize>, xs: &mut Vec<usize>, used: &mut Vec<bool>, n_in: &mut Vec<usize>, ans: &mut Vec<Vec<usize>>, g: &Vec<Vec<usize>>, k: usize) {
    // dbg!(&que, &xs);
    if que.len() == 0 {
        if xs.len() == g.len() {
            ans.push(xs.clone());
        }
        return;
    }
    for _ in 0..que.len() {
        let v = que.pop_front().unwrap();
        if !used[v] {
            xs.push(v);
            used[v] = true;
            for &u in &g[v] {
                if !used[u] {
                    n_in[u] -= 1;
                    if n_in[u] == 0 {
                        que.push_back(u);
                    }
                }
            }
            dfs(que, xs, used, n_in, ans, g, k);

            for &u in &g[v] {
                if !used[u] {
                    n_in[u] += 1;
                    if n_in[u] == 1 {
                        que.pop_back();
                    }
                }
            }
            used[v] = false;
            xs.pop();
            que.push_back(v);
        }

        if ans.len() == k {
            return;
        }
    }
}