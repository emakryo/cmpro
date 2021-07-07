fn main() {
    proconio::input! { mut n: u64 }
    let mut x: u32 = 0;
    for i in 2..n {
        if i*i>n { break }
        while n % i == 0 {
            x += 1;
            n /= i;
        }
    }
    if n > 1 {
        x += 1;
    }

    dbg!(x);

    let mut ans = 0;
    if x.is_power_of_two() {
        ans = -1;
    }
    while x > 0 {
        x >>= 1;
        ans += 1;
    }
    println!("{}", ans);
}