fn query(i: usize) -> i32 {
    println!("? {}", i);
    let stdin = std::io::stdin();
    proconio::input!{
        from proconio::source::line::LineSource::new(stdin.lock()),
        n: i32,
    }
    n
}

fn solve() {
    let n = {
        let stdin = std::io::stdin();
        proconio::input!{
            from proconio::source::line::LineSource::new(stdin.lock()),
            n: usize,
        }
        n
    };

    let m = 1597;
    let mut a = vec![None; m];
    a[0] = Some(-1);
    for i in (n+1)..m {
        a[i] = Some(n as i32 - i as i32);
    }
    let (mut l, mut r) = (0, m);
    let (mut x, mut y) = (610, 987);
    for _ in 0..14 {
        if a[x].is_none() {
            a[x] = Some(query(x));
        }
        if a[y].is_none() {
            a[y] = Some(query(y));
        }
        if a[x] < a[y] {
            let nx = y;
            let ny = r - (y - x);
            let nl = x;
            let nr = r;
            x = nx;
            y = ny;
            l = nl;
            r = nr;
        } else {
            let nx = l + (y - x);
            let ny = x;
            let nl = l;
            let nr = y;
            x = nx;
            y = ny;
            l = nl;
            r = nr;
        }
        // dbg!((l, x, y, r));
    }
    let ans = a.into_iter().filter_map(|x| x).max();
    println!("! {}", ans.unwrap());
}

fn main() {
    // let v: Vec<_> = (0..16).scan((1, 1), |(a, b), _| {
    //     let t = *a;
    //     *a += *b;
    //     *b = t;
    //     Some(t)
    // }).collect();
    // dbg!(v);
    let t = {
        let stdin = std::io::stdin();
        proconio::input!{
            from proconio::source::line::LineSource::new(stdin.lock()),
            t: usize,
        }
        t
    };
    for _ in 0..t {
        solve();
    }
}