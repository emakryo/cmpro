fn rec(u: usize, p: Option<usize>, g: &Vec<Vec<usize>>) -> (usize, usize) {
    let mut depths = vec![];
    let mut ret = 0;
    for &v in &g[u] {
        if let Some(p) = p {
            if p == v {
                continue;
            }
        }
        let (dia, depth) = rec(v, Some(u), g);

        ret = ret.max(dia);
        depths.push(depth);
    }

    depths.sort();

    let depth = depths.last().map(|x| *x+1).unwrap_or(0);
    ret = ret.max(depth);
    if depths.len() >= 2 {
        let n = depths.len();
        ret = ret.max(2 + depths[n-1] + depths[n-2]);
    }

    // dbg!(u, ret, depth, &depths);

    (ret, depth)
}

fn main() {
    proconio::input! {
        n: usize,
        e: [(usize, usize); n-1],
    }

    let g = {
        let mut g = vec![vec![]; n];
        for (a, b) in e {
            g[a-1].push(b-1);
            g[b-1].push(a-1);
        }
        g
    };

    let ans = rec(0, None, &g);
    
    println!("{}", ans.0+1);
}