#![allow(unused_macros, unused_imports)]

use std::collections::{HashSet, VecDeque};
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
        (x, y): (i64, i64),
        ps: [(i64, i64); n],
    }

    let offset = 300;
    let x = (x + offset as i64) as usize;
    let y = (y + offset as i64) as usize;
    let ps = ps.into_iter().map(|(x, y)| {
        ((x+offset as i64) as usize, (y+offset as i64) as usize)
    }).collect::<HashSet<_>>();
    let inf = 100000000;
    let lim = 600;
    let mut dist = vec![vec![inf; lim]; lim];
    let mut visit = vec![vec![false; lim]; lim];
    let mut que = VecDeque::new();
    
    que.push_back((offset, offset));
    dist[offset][offset] = 0;
    visit[offset][offset] = true;

    while let Some((a, b)) = que.pop_front() {
        if (a, b) == (x, y) {
            println!("{}", dist[x][y]);
            return;
        }

        let dx = [1, 0, -1, 1, -1, 0];
        let dy = [1, 1, 1, 0, 0, -1];

        for k in 0..6 {
            let nx = a as i64 + dx[k];
            let ny = b as i64 + dy[k];
            if nx < 0 || lim as i64 <= nx || ny < 0 || lim as i64 <= ny {
                continue;
            }
            let nx = nx as usize;
            let ny = ny as usize;
            if ps.contains(&(nx, ny)) || visit[nx][ny] {
                continue;
            }

            dist[nx][ny] = dist[a][b] + 1;
            visit[nx][ny] = true;
            que.push_back((nx, ny));
        }
    }

    println!("-1");
}