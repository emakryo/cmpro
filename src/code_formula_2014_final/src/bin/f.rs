#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        #[cfg(debug_assertions)]
        std::dbg!($($xs),+)
    }
}

fn main() {

    let mut ans = vec![];
    let mut inc = vec![vec![false; 1500]; 1500];
    for i in (1..=100).rev() {
        let f = || {
            for x in i..=1500-i {
                for y in i..=1500-i {
                    if inc[x][y] { continue }
                    let mut ok = true;
                    for &(k, xk, yk) in &ans {
                        let dx = if x > xk { x - xk } else { xk - x };
                        let dy = if y > yk { y - yk } else { yk - y };
                        if dx*dx+dy*dy < (i+k)*(i+k) {
                            ok = false;
                        }
                    }
                    if ok {
                        return (x, y);
                    }
                }
            }
            return (0, 0);
        };
        let (xi, yi) = f();
        for x in 0..1500 {
            for y in 0..1500 {
                let dx = if x > xi { x - xi } else { xi - x };
                let dy = if y > yi { y - yi } else { yi - y };
                if dx*dx+dy*dy <= i*i {
                    inc[x][y] = true;
                }
            }
        }
        ans.push((i, xi, yi));
    }

    plot(&ans);

    for (_, x, y) in ans.into_iter().rev() {
        println!("{} {}", x, y);
    }
}

fn plot(circles: &[(usize, usize, usize)]) {
    use plotters::prelude::*;

    let root = BitMapBackend::new("out.png", (500, 500)).into_drawing_area();
    root.fill(&WHITE).unwrap();
    for (r, x, y) in circles {
        root.draw(&Circle::new((*x as i32 / 3, *y as i32 / 3), *r as i32 / 3, ShapeStyle::from(&GREEN).filled())).unwrap();
    }
}