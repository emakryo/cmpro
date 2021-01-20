// cargo-deps: regex="1"
use std::io::BufRead;

#[derive(Debug)]
enum Rule {
    Char(char),
    Sub(Vec<Vec<usize>>),
}

fn build_regex(n: usize, rules: &[Rule], memo: &mut Vec<Option<String>>) -> String {
    if let Some(x) = &memo[n] {
        return x.to_string()
    }

    let r = match &rules[n] {
        Rule::Char(c) => {
            c.to_string()
        }
        Rule::Sub(xss) => {
            let mut r = "".to_string();
            for xs in xss {
                let mut s = "".to_string();
                for x in xs {
                    s.push_str(&format!("{}", build_regex(*x, rules, memo)));
                }

                if &r == "" {
                    r.push_str(&format!("({})", s));
                } else {
                    r.push_str(&format!("|({})", s));
                }
            }

            format!("({})", r)
        }
    };

    memo[n] = Some(r.clone());

    r
}

fn parse(x: &str) -> (usize, Rule) {
    let re = regex::Regex::new(r#"^(\d+): (?:"(.)"|([0-9 ]+)(?: \| ([0-9 ]+))?)$"#).unwrap();

    let cap = re.captures(x).unwrap();

    let n = cap[1].parse::<usize>().unwrap();

    if let Some(c) = cap.get(2) {
        (n, Rule::Char(c.as_str().chars().next().unwrap()))
    } else {
        let mut xs = vec![];
        
        if let Some(x) = cap.get(3) {
            xs.push(x.as_str().split_whitespace().map(|s| s.parse::<usize>().unwrap()).collect());
        }
        if let Some(x) = cap.get(4) {
            xs.push(x.as_str().split_whitespace().map(|s| s.parse::<usize>().unwrap()).collect());
        }

        (n, Rule::Sub(xs))
    }
}

fn main() {
    let xs: Vec<_> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>().unwrap();

    let mut xs = xs.iter();
    let mut rules = vec![];

    loop {
        let line = xs.next().unwrap().trim();
        if line == "" {
            break;
        }
        rules.push(parse(&line));
    }

    rules.sort_by_key(|x| x.0);

    let rules: Vec<_> = rules.into_iter().map(|x| x.1).collect();

    dbg!(&rules[8]);

    let mut memo = vec![None; rules.len()];
    // let re = build_regex(0, &rules, &mut memo);
    // let re = regex::Regex::new(&format!("^{}$", &re)).unwrap();
    let r42 = build_regex(42, &rules, &mut memo);
    let r31 = build_regex(31, &rules, &mut memo);

    let res: Vec<_> = (1..50).map(|i| {
        regex::Regex::new(&format!(
            "^{}{{{},}}{}{{{}}}$",
            r42,
            i+1,
            r31,
            i,
        )).unwrap()
    }).collect();
    dbg!(&memo.len());

    let mut all = 0;
    let mut matches = 0;
    let mut max_len = 0;
    while let Some(line) = xs.next() {
        let line = line.trim();
        max_len = std::cmp::max(max_len, line.len());
        all += 1;
        dbg!(&line);
        for i in 0..49 {
            dbg!(i);
            if res[i].is_match(&line) {
                matches += 1;
                break;
            }
        }
    }
    dbg!(max_len);
    dbg!(all);
    dbg!(matches);
}
