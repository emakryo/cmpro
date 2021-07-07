fn main() {
    proconio::input! {
        n: usize,
        xs: [(usize, usize, usize); n],
    }

    let t: Vec<_> = xs.iter().cloned().map(|(x, _, _)| x).collect();
    let l: Vec<_> = xs.iter().cloned().map(|(_, x, _)| x).collect();
    let r: Vec<_> = xs.iter().cloned().map(|(_, _, x)| x).collect();

    let mut ans = 0;
    for i in 0..n {
        for j in (i+1)..n {
            if r[i] < l[j] || r[j] < l[i] { continue }
            if r[i] == l[j] && !((t[i]==1||t[i]==3) && (t[j]==1||t[j]==2)) {
                continue;
            }
            if r[j] == l[i] && !((t[i]==1||t[i]==2) && (t[j]==1||t[j]==3)) {
                continue;
            }
            ans += 1;
        }
    }

    println!("{}", ans);
}