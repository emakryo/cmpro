#![allow(unused_macros, unused_imports)]
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

fn main() {
    proconio::input!{
        n: usize,
        s: u64,
        d: [u32; n],
    }

    let mut lb = 0;
    let mut ub = 0;
    for i in 0..n {
        lb += 10u64.pow(d[i]-1);
        ub += 10u64.pow(d[i])-1;
    }

    if s < lb || ub < s {
        println!("-1");
        return;
    }

    let mut t = s;
    let mut ans = vec![];
    for i in 0..n {
        let mut x = t;
        for j in i+1..n {
            if x < 10u64.pow(d[j])-1 {
                x = 0;
                break;
            }
            x -= 10u64.pow(d[j])-1;
        }
        x = x.max(10u64.pow(d[i]-1));
        t -= x;
        ans.push(x);
    }

    assert_eq!(ans.iter().sum::<u64>(), s);

    println!("{}", ans.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(" "));
}