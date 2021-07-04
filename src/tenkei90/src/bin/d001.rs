fn main() {
    proconio::input! {
        n: usize,
        l: usize,
        k: usize,
        mut a: [usize; n],
    };
    a.push(l);

    let (mut lb, mut ub) = (0, 1_000_000_005);

    while ub-lb > 1 {
        let x = (ub+lb)/2;
        
        let mut i = 0;
        let mut m = 0;
        let mut s = 0;
        while i<=n {
            while i<=n && a[i]-s<x {
                i += 1
            }
            if i==n+1 {
                break;
            }
            m += 1;
            s = a[i];
        }

        if m >= k+1 {
            lb = x;
        } else {
            ub = x;
        }
    }

    println!("{}", lb);
}