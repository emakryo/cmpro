fn main() {
    proconio::input! {
        n: usize,
        d: u32,
        a: [usize; n],
    }

    let mut ans = 0;
    for b in 0..(1<<n) {
        let mut c = 0;
        let mut k = 0;
        for i in 0..n {
            if b>>i&1 == 1 {
                c = c | a[i];
                k += 1;
            }
        }

        let m = 1i64 << (d - c.count_ones());
        dbg!(ans, m);
        if k%2 == 0 {
            ans += m;
        } else {
            ans -= m;
        }
    }

    println!("{}", ans);
}