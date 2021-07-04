fn main() {
    proconio::input! {
        a: usize,
        b: usize,
    }

    if a <= b && b <= 6*a {
        println!("Yes");
    } else {
        println!("No");
    }
}