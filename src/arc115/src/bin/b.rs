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
        c: [[usize; n]; n],
    }

    let sumx: Vec<usize> = c.iter().map(|ci| ci.iter().sum::<usize>()).collect();
    let sum: usize = sumx.iter().sum();
    if sum % n > 0 {
        println!("No");
        return;
    }

    let bsum = sumx.iter().min().unwrap();
    let mut a = vec![];
    for i in 0..n {
        if (sumx[i]-bsum) % n != 0 {
            println!("No");
            return;
        }
        a.push((sumx[i]-bsum)/n);
    }
    let asum: usize = a.iter().sum();
    dbg!(&a);
    let mut sumy = vec![0; n];
    for i in 0..n {
        for j in 0..n {
            sumy[j] += c[i][j];
        }
    }
    let mut b = vec![];
    for i in 0..n {
        if (sumy[i]-asum) % n != 0 {
            println!("No");
            return;
        }
        b.push((sumy[i]-asum)/n);
    }

    let a: Vec<_> = a.iter().map(usize::to_string).collect();
    let b: Vec<_> = b.iter().map(usize::to_string).collect();

    println!("Yes");
    println!("{}", a.join(" "));
    println!("{}", b.join(" "));
}