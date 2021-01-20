// cargo-deps: regex="1"

use std::collections::{HashMap, HashSet};
use std::io::BufRead;
#[derive(Debug, Clone)]
struct Edge {
    to: usize,
    rev: usize,
}

#[derive(Debug)]
pub struct Flow {
    graph: Vec<Vec<Edge>>,
    capacity: Vec<Vec<u64>>,
}

struct FlowData {
    capacity: Vec<Vec<u64>>,
    visit: Vec<bool>,
}

impl Flow {
    pub fn new(n: usize) -> Self {
        Flow {
            graph: vec![vec![]; n],
            capacity: vec![vec![]; n],
        }
    }

    pub fn add_edge(&mut self, from: usize, to: usize, cap: u64) {
        assert!(from != to);
        let rev = self.graph[to].len();
        self.graph[from].push(Edge { to, rev });
        self.capacity[from].push(cap);
        let rev = self.graph[from].len()-1;
        self.graph[to].push(Edge { to: from, rev });
        self.capacity[to].push(0);
    }

    pub fn max_flow(&mut self, source: usize, sink: usize) -> u64 {
        let n = self.graph.len();
        let mut f = 0;
        let mut data = FlowData {
            capacity: self.capacity.clone(),
            visit: vec![false; n],
        };
        loop {
            let d = self.dfs(&mut data, source, sink, u64::MAX);
            if d == 0 {
                self.capacity = data.capacity;
                return f;
            }
            f += d;
            data.visit = vec![false; n];
        }
    }

    fn dfs(&self, data: &mut FlowData, node: usize, sink: usize, flow: u64) -> u64 {
        if node == sink {
            return flow;
        }
        data.visit[node] = true;
        for (i, e) in self.graph[node].iter().enumerate() {
            if data.visit[e.to] || data.capacity[node][i] == 0 {
                continue;
            }
            let d = self.dfs(data, e.to, sink, std::cmp::min(data.capacity[node][i], flow));
            if d > 0 {
                data.capacity[node][i] -= d;
                data.capacity[e.to][e.rev] += d;
                return d;
            }
        }
        return 0;
    }
}

fn main() {
    let lines: Vec<_> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>().unwrap();


    let re = regex::Regex::new(r"^([a-z ]+) \(contains ([a-z ,]+)\)$").unwrap();

    let mut ingredients: Vec<HashSet<String>> = vec![];
    let mut allergens: Vec<HashSet<String>> = vec![];

    let mut all_ingredients: HashSet<String> = HashSet::new();
    let mut all_allergens: HashSet<String> = HashSet::new();

    for line in &lines {
        let capture = re.captures(line).unwrap();
        let igs: HashSet<_> = capture[1].split_whitespace().map(|s| s.to_string()).collect();
        let als: HashSet<_> = capture[2].split(", ").map(|s| s.to_string()).collect();

        for ig in &igs {
            all_ingredients.insert(ig.clone());
        }

        for al in &als {
            all_allergens.insert(al.clone());
        }

        ingredients.push(igs);
        allergens.push(als);
    }

    let ingredients_index: HashMap<String, usize> = all_ingredients
        .into_iter()
        .enumerate()
        .map(|(i, s)| (s, i))
        .collect();

    let allergens_index: HashMap<String, usize> = all_allergens
        .into_iter()
        .enumerate()
        .map(|(i, s)| (s, i + ingredients_index.len()))
        .collect();

    let source_index = ingredients_index.len() + allergens_index.len();
    let sink_index = source_index + 1;

    let mut flow = Flow::new(sink_index+1);

    for n in ingredients_index.values() {
        flow.add_edge(*n, sink_index, 1);
    }

    for (al, n) in &allergens_index {
        let mut intersect: Option<HashSet<String>> = None;
        for (igs, als) in ingredients.iter().zip(allergens.iter()) {
            if !als.contains(al) {
                continue;
            }

            if let Some(is) = intersect {
                intersect = Some(is.intersection(igs).cloned().collect());
            } else {
                intersect = Some(igs.clone());
            }
        }

        let intersect = intersect.unwrap();

        dbg!(al, &intersect);

        flow.add_edge(source_index, *n, 1);
        for ig in &intersect {
            flow.add_edge(*n, *ingredients_index.get(ig).unwrap(), 1);
        }
    }

    flow.max_flow(source_index, sink_index);

    let mut ingredients_with_allergen = vec![];
    for (al, m) in &allergens_index {
        let e = flow.capacity[*m]
            .iter()
            .zip(flow.graph[*m].iter())
            .filter(|(c, e)| {
                **c == 0 && e.to < ingredients_index.len()
            })
            .collect::<Vec<_>>();

        dbg!(al);
        dbg!(&e);

        let ig = ingredients_index.iter().filter(|(_, n)| **n == e[0].1.to).next().unwrap().0.clone();
        ingredients_with_allergen.push((al.clone(), ig.clone()));
    }


    // for igs in &ingredients {
    //     for ig in igs {
    //         if !ingredients_with_allergen.contains(ig) {
    //             count += 1;
    //         }
    //     }
    // }

    ingredients_with_allergen.sort();
    let list = ingredients_with_allergen.into_iter().map(|(_, s)| s).collect::<Vec<_>>().join(",");
    dbg!(list);
}