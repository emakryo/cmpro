#[proconio::fastout]
fn main() {
    proconio::input! {
        n: usize,
    };

    if n%2 > 0 {
        return;
    }

    let mut ans = vec![String::from("(")];
    for i in 1..n {
        let mut next = vec![];
        for mut s in ans {
            let o = s.bytes().filter(|c| *c==b'(').count() - s.bytes().filter(|c| *c==b')').count();
            if o+1 <= n-i-1 {
                let mut s = s.clone();
                s.push('(');
                next.push(s);
            }

            if o > 0 {
                s.push(')');
                next.push(s);
            }
        }

        ans = next;
    }

    for a in ans {
        println!("{}", a);
    }
}