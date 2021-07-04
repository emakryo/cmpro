fn main() {
    proconio::input! {
        h: usize,
        w: usize,
        c: [proconio::marker::Bytes; h],
    }

    let mut dp = vec![vec![vec![false; 1<<(h*w)]; h*w]; h*w];

    let mut ans = -1;
    for s in 1usize..(1<<(h*w)) {
        let k = s.count_ones();
        if k == 1 {
            let i = s.trailing_zeros() as usize;
            if c[i%h][i/h] == b'.' { 
                dp[i][i][s] = true;
            }
        }

        for i in 0..(h*w) {
            for b in 0..(h*w) {
                if !dp[i][b][s] { continue; }
                let (x, y) = ((i%h) as i32, (i/h) as i32);
                let dx = [0, -1, 0, 1];
                let dy = [-1, 0, 1, 0];

                for k in 0..4 {
                    let (x, y) = (x + dx[k], y + dy[k]);

                    if x < 0 || h as i32 <= x || y < 0 || w as i32 <= y {
                        continue;
                    }
                    if c[x as usize][y as usize] == b'#' {
                        continue;
                    }
                    let (x, y) = (x as usize, y as usize);
                    let j = x + h * y;
                    let t = s | 1 << j;
                    if j == b {
                        ans = ans.max(t.count_ones() as i32);
                    }
                    if s>>j&1 > 0 {
                        continue;
                    }

                    dp[j][b][t] = true;
                }
            }
        }
    }

    if ans <= 2 {
        ans = -1;
    }
    println!("{}", ans);
}