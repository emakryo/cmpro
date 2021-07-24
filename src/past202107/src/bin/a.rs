fn main() {
    proconio::input! {
        s: proconio::marker::Bytes,
    }

    let mut x = 0;
    for i in 0..14 {
        if i%2==0 {
            x += 3*(s[i]-b'0');
        } else {
            x += s[i]-b'0';
        }
    }
    if s[14] - b'0' == x % 10 {
        println!("Yes");
    } else {
        println!("No");
    }
}