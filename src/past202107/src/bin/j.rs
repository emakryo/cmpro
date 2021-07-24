#![allow(unused_macros)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}
use proconio::marker::Usize1;
fn main() {
    proconio::input!{
        n: usize,
        m: usize,
        es: [(Usize1, Usize1); m],
    }

    let mut g = vec![vec![]; n];
    for (u, v) in es {
        g[u].push(v);
    }

    let mut visit = vec![0; n];
    for i in 0..n {
        if visit[i] == 2 { continue }
        if dfs(i, &mut visit, &g) {
            println!("Yes");
            return;
        }
    }
    println!("No");
}

fn dfs(u: usize, visit: &mut Vec<usize>, g: &Vec<Vec<usize>>) -> bool {
    visit[u] = 1;
    for &v in &g[u] {
        if visit[v] == 1 {
            return true;
        }

        if visit[v] == 0 {
            if dfs(v, visit, g) {
                return true;
            }
        }
    }
    visit[u] = 2;
    return false;
}