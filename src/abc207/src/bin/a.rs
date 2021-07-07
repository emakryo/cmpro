fn main() {
    proconio::input! {
        a: usize,
        b: usize,
        c: usize,
    }
    println!("{}", (a+b).max(b+c).max(c+a));
}