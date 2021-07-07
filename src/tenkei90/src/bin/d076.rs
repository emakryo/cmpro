fn main() {
    proconio::input! {
        n: usize,
        mut a: [usize; n],
    }
    let sum = a.iter().sum::<usize>();
    a.extend(a.clone());
    
    let (mut i, mut j) = (0, 0);
    let mut x = 0;
    while j < a.len() {
        if x * 10 == sum {
            println!("Yes");
            return;
        }
        if x * 10 < sum {
            x += a[j];
            j += 1;
        } else {
            x -= a[i];
            i += 1;
        }
    }
    println!("No");
}