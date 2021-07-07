use std::collections::HashSet;

fn main() {
    proconio::input!{
        n: usize,
        mut s: [(f64, f64); n],
        mut t: [(f64, f64); n],
    }

    if n==1 {
        println!("Yes");
        return;
    }

    let so = s[0];
    for i in 0..n {
        s[i].0 -= so.0;
        s[i].1 -= so.1;
    }

    let rs = s[1].0.hypot(s[1].1);
    let ts = s[1].0.atan2(s[1].1);

    let s = {
        let mut ss = HashSet::new();
        for p in s {
            ss.insert((p.0 as i32, p.1 as i32));
        }
        ss
    };


    for i in 0..n { // origin
        let to = t[i];
        for j in 0..n {
            t[j].0 -= to.0;
            t[j].1 -= to.1;
        }

        for j in 0..n { // 1
            if i==j { continue; }
            let rt = t[j].0.hypot(t[j].1);
            let tt = t[j].0.atan2(t[j].1);

            if (rt - rs).abs() > 1e-3 {
                continue;
            }

            let rot = tt-ts;

            let u = t.iter().map(|(x, y)| {
                (x * rot.cos() - y * rot.sin(), x * rot.sin() + y * rot.cos())
            }).collect::<Vec<_>>();

            let mut ok = true;
            for k in 0..n {
                if (u[k].0 - u[k].0.round()).abs() > 1e-3 { ok = false; continue; }
                let x = u[k].0.round() as i32;
                if (u[k].1 - u[k].1.round()).abs() > 1e-3 { ok = false; continue; }
                let y = u[k].1.round() as i32;
                if !s.contains(&(x, y)) { ok = false; }
            }

            if ok {
                println!("Yes");
                return;
            }
        }
    }

    println!("No");
    return;
}