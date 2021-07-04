#[proconio::fastout]
fn main() {
    proconio::input! {
        h: usize,
        w: usize,
        a: [[usize; w]; h],
    }

    let mut r = vec![0; h];
    let mut c = vec![0; w];

    for i in 0..h {
        for j in 0..w {
            r[i] += a[i][j];
            c[j] += a[i][j];
        }
    }

    for i in 0..h {
        for j in 0..w {
            print!("{}{}", r[i]+c[j]-a[i][j], if j==w-1 { '\n' } else { ' ' });
        }
    }
}