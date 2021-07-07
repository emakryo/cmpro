fn main() {
    proconio::input! {
        a: usize,
        b: usize,
        c: usize,
        d: usize,
    }

    if d*c <= b {
        println!("-1");
    } else {
        let z = d*c-b;
        println!("{}", (a+z-1) / z);
    }
}