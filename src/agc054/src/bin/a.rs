fn main() {
    proconio::input!{
        n: usize,
        s: proconio::marker::Bytes,
    }

    let ans;
    if s[0] != s[n-1] {
        ans = 1;
    } else {
        let mut ok = false;
        for i in 1..(n-1) {
            if s[i] != s[0] && s[i+1] != s[0] {
                ok = true;
            }
        }
        if ok {
            ans = 2;
        } else {
            ans = -1;
        }
    }

    println!("{}", ans);

}