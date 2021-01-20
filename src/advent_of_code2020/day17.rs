use std::io::BufRead;

type V4 = Vec<Vec<Vec<Vec<char>>>>;

fn step(space: &V4, next: &mut V4) {
    let x = space.len();
    let y = space[0].len();
    let z = space[0][0].len();
    let w = space[0][0][0].len();

    for i in 0..x {
        for j in 0..y {
            for k in 0..z {
                for l in 0..w {
                    let mut cnt = 0;
                    for dx in -1..=1 {
                        for dy in -1..=1 {
                            for dz in -1..=1 {
                                for dw in -1..=1 {
                                    if dx == 0 && dy == 0 && dz == 0 && dw == 0 {
                                        continue;
                                    }
                                    let ni = i as i32 + dx;
                                    let nj = j as i32 + dy;
                                    let nk = k as i32 + dz;
                                    let nl = l as i32 + dw;
                                    if ni < 0 || x as i32 <= ni || nj < 0 || y as i32 <= nj || nk < 0 || z as i32 <= nk || nl < 0 || w as i32 <= nl {
                                        continue
                                    }
                                    if space[ni as usize][nj as usize][nk as usize][nl as usize] == '#' {
                                        cnt += 1;
                                    }
                                }
                            }
                        }
                    }

                    next[i][j][k][l] = if cnt == 3 {
                        '#'
                    } else if cnt == 2 && space[i][j][k][l] == '#' {
                        '#'
                    } else {
                        '.'
                    }
                }
            }
        }

    }

}

fn main() {
    let xs: Vec<Vec<_>> = std::io::stdin()
        .lock()
        .lines()
        .map(|s| s.unwrap().trim().to_string().chars().collect())
        .collect();

    let h = xs.len();
    let w = xs[0].len();
    dbg!(h, w);

    let mut space = vec![vec![vec![vec!['.'; h+12]; w+12]; 13]; 13];
    for i in 0..h {
        for j in 0..w {
            space[6][6][j+6][i+6] = xs[i][j];
        }
    }

    let mut next = vec![vec![vec![vec!['.'; h+12]; w+12]; 13]; 13];

    for _ in 0..6 {
        step(&space, &mut next);
        std::mem::swap(&mut space, &mut next);
    }

    let mut x = 0;
    for i in 0..13 {
        for l in 0..13 {
            for j in 0..(w+12) {
                for k in 0..(h+12) {
                    if space[i][l][j][k] == '#' {
                        x += 1;
                    }
                }
            }
        }
    }

    dbg!(x);
}