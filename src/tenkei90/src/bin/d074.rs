fn main() {
    proconio::input! {
        n: usize,
        s: proconio::marker::Bytes,
    }

    let mut ans = 0;
    for i in 0..n {
        if s[i] == b'b' {
            ans += 1u64 << i;
        } else if s[i] == b'c' {
            ans += 1 << i + 1;
        }
    }
    println!("{}", ans);
}