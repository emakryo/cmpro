#![allow(unused_macros, unused_imports)]

use std::collections::VecDeque;

use proconio::marker::Chars;
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
        h: usize,
        w: usize,
        s: [Chars; h],
    }

    let inf = 1000000000u64;
    let mut dist = vec![vec![inf; w]; h];
    let mut que = VecDeque::new();

    dist[0][0] = 0;
    que.push_back((0, 0));

    while let Some((x, y)) = que.pop_front() {
        let dx = [0, 1, 0, -1];
        let dy = [1, 0, -1, 0];
        for k in 0..4 {
            let nx = x + dx[k];
            let ny = y + dy[k];

            if (0..h as i32).contains(&nx) && (0..w as i32).contains(&ny) && s[nx as usize][ny as usize] == '.' {
                let x = x as usize;
                let y = y as usize;
                let nx = nx as usize;
                let ny = ny as usize;
                if dist[x][y] < dist[nx][ny] {
                    que.push_front((nx as i32, ny as i32));
                    dist[nx][ny] = dist[x][y];
                }
            }
        }

        for i in -2..=2i32 {
            for j in -2..=2i32 {
                if i.abs() == 2 && j.abs() == 2 {
                    continue;
                }

                if (i, j) == (0, 0) {
                    continue;
                }

                let nx = x + i;
                let ny = y + j;

                if (0..h as i32).contains(&nx) && (0..w as i32).contains(&ny) {
                    let x = x as usize;
                    let y = y as usize;
                    let nx = nx as usize;
                    let ny = ny as usize;
                    if dist[x][y] + 1 < dist[nx][ny] {
                        que.push_back((nx as i32, ny as i32));
                        dist[nx][ny] = dist[x][y] + 1;
                    }
                }
            }
        }
    }

    println!("{}", dist[h-1][w-1]);
}


