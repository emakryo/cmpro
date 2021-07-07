fn main() {
    proconio::input! {
        h: usize,
        w: usize,
        a: [[i64; w]; h],
        mut b: [[i64; w]; h],
    }

    let mut ans = 0;
    for i in 0..(h-1) {
        for j in 0..(w-1) {
            let d = a[i][j] -  b[i][j];
            ans += d.abs();
            b[i][j] += d;
            b[i+1][j] += d;
            b[i][j+1] += d;
            b[i+1][j+1] += d;
        }
    }

    for i in 0..h {
        for j in 0..w {
            if a[i][j] != b[i][j] {
                println!("No");
                return;
            }
        }
    }
    println!("Yes\n{}", ans);
}