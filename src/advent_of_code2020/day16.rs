// cargo-deps: regex="1",anyhow="1"
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

fn main() -> anyhow::Result<()> {
    let xs: Vec<_> = std::io::stdin()
        .lock()
        .lines()
        .collect::<Result<_, _>>()?;
    let mut xs = xs.iter();

    let re_field = regex::Regex::new(r"([a-zA-Z\s]+): (\d+)-(\d+) or (\d+)-(\d+)")?;
    let mut fields = std::collections::HashMap::<String, Vec<(u64, u64)>>::new();
    while let Some(line) = xs.next() {
        if let Some(cap) = re_field.captures(&line) {
            let r: Vec<u64> = (2..cap.len()).map(|i| cap[i].parse().unwrap()).collect();
            fields.insert(cap[1].to_string(), vec![(r[0], r[1]), (r[2], r[3])]);
        } else {
            break;
        }
    }

    dbg!(&fields.len());

    xs.next();
    let your: Vec<u64> = xs.next().unwrap().split(',').map(|x| x.parse().unwrap()).collect();
    dbg!(&your.len());

    xs.next();
    xs.next();
    let mut near: Vec<Vec<u64>> = vec![];
    
    while let Some(line) = xs.next() {
        near.push(line.split(',').map(|x| x.parse().unwrap()).collect());
    }
    dbg!(&near.len());

    let mut valid = vec![];
    for xs in near {
        let mut ok = true;
        for x in &xs {
            let mut included = false;
            for rs in fields.values() {
                for (s, t) in rs {
                    if s <= x && x <= t {
                        included = true;
                    }
                }
            }
            ok = ok && included;
        }

        if ok {
            valid.push(xs);
        }
    }

    dbg!(valid.len());

    let n = your.len();
    let mut flow = Flow::new(2*n+2);
    let mut fields: Vec<(_, _)> = fields.iter().collect();
    fields.sort();

    for (i, (name, rs)) in fields.iter().enumerate() {
        for j in 0..n {
            let mut ok = 0;
            for k in 0..valid.len() {
                if rs[0].0 <= valid[k][j] && valid[k][j] <= rs[0].1 ||
                    rs[1].0 <= valid[k][j] && valid[k][j] <= rs[1].1 {
                    ok += 1;
                }
            }

            if ok == valid.len() {
                flow.add_edge(i, n+j, 1);
            }
        }

        flow.add_edge(2*n, i, 1);
        flow.add_edge(n+i, 2*n+1, 1);
    }

    flow.max_flow(2*n, 2*n+1);

    let mut prod = 1;
    for (i, (name, rs)) in fields.iter().enumerate() {
        let mut k = 0;
        for (j, e) in flow.graph[i].iter().enumerate() {
            if flow.capacity[i][j] == 0 {
                k = dbg!(flow.graph[i][j].to-n);
            }
        }

        if name.starts_with("departure") {
            // dbg!(your[k], prod);
            prod *= your[k];
        }
    }

    dbg!(prod);

    Ok(())
}