use proconio::marker::Usize1;
fn main() {
    proconio::input! {
        n: usize,
        m: usize,
        es: [(Usize1, Usize1); m],
    }

    let mut g = vec![vec![]; n];
    for (a, b) in es {
        g[a].push(b);
        g[b].push(a);
    }

    let mut ans = 0;
    for i in 0..n {
        g[i].sort();
        let mut c = 0;
        for v in &g[i] {
            if *v < i {
                c += 1;
            }
        }

        if c==1 {
            ans += 1;
        }
    }

    println!("{}", ans);
}