// cargo-deps: nom="6"
use std::io::BufRead;
use nom::{
    branch::alt, sequence::{preceded, pair, delimited}, bytes::complete::tag, IResult,
    combinator::{all_consuming, map}, character::complete::digit1,
    multi::many0,
};

fn term(exp: &str) -> IResult<&str, i64> {
    alt((
        map(digit1, |x: &str| x.parse::<i64>().unwrap()),
        delimited(tag("("), eval_mul, tag(")")),
    ))(exp)
}

fn eval_add(exp: &str) -> IResult<&str, i64> {
    map(
        pair(
            term,
            many0(preceded(tag(" + "), term)),
        ),
        |(mut x, ys)| {
            for y in ys {
                x += y;
            }
            x
        }
    )(exp)
}

fn eval_mul(exp: &str) -> IResult<&str, i64> {
    map(
        pair(
            eval_add,
            many0(preceded(tag(" * "), eval_add)),
        ),
        |(mut x, ys)| {
            for y in ys {
                x *= y;
            }
            x
        }
    )(exp)
}

fn main() {
    let xs: Vec<_> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>().unwrap();

    let mut ans = 0;
    for exp in &xs {
        ans += all_consuming(eval_mul)(exp.trim()).unwrap().1;
    }

    dbg!(ans);
}