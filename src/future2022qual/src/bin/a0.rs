#![allow(unused_macros, unused_imports)]

use std::{collections::VecDeque, io::BufRead, iter::FromIterator};

use proconio::marker::Usize1;
use rand::distributions::Standard;
macro_rules! dbg {
    ($($xs:expr),+) => {
        if cfg!(debug_assertions) {
            std::dbg!($($xs),+)
        } else {
            ($($xs),+)
        }
    }
}

struct State {
    n: usize,
    m: usize,
    k: usize,
    r: usize,
    d: Vec<Vec<u64>>,
    graph: Vec<Vec<usize>>,
    num_dep: Vec<u64>,
    ready_tasks: Vec<usize>,
    current_task: Vec<Option<usize>>,
    complete_tasks: Vec<Vec<(usize, u64)>>,
    task_begin: Vec<u64>,
    free_members: VecDeque<usize>,
    step: u64,
    skill_lb: Vec<Vec<f64>>,
}

impl State {
    fn new(
        n: usize,
        m: usize,
        k: usize,
        r: usize,
        d: Vec<Vec<u64>>,
        es: Vec<(usize, usize)>,
    ) -> Self {
        let mut graph = vec![vec![]; n];
        let mut num_dep = vec![0; n];
        for (a, b) in es {
            graph[a].push(b);
            num_dep[b] += 1;
        }

        let mut ready_tasks = vec![];
        for i in 0..n {
            if num_dep[i] == 0 {
                ready_tasks.push(i);
            }
        }

        let current_task = vec![None; m];
        let complete_tasks = vec![vec![]; m];
        let task_begin = vec![0; n];
        let free_members = VecDeque::from_iter(0..m);
        let step = 0;
        let skill_lb = vec![vec![0.0; k]; m];

        Self {
            n, m, k, r, d, graph, num_dep, ready_tasks, current_task, complete_tasks, task_begin, free_members, step, skill_lb
        }
    }

    fn assign(&mut self) -> Vec<(usize, usize)> {
        let mut next_ready_tasks = vec![];
        let mut assign = vec![];
        for &r in &self.ready_tasks {
            if let Some(p) = self.free_members.pop_front() {
                assign.push((p, r));
                self.current_task[p] = Some(r);
                self.task_begin[r] = self.step;
            } else {
                next_ready_tasks.push(r);
            }
        }

        self.ready_tasks = next_ready_tasks;

        assign
    }

    fn finish(&mut self, finished_members: &[usize]) {
        for &p in finished_members {
            let task = self.current_task[p].unwrap();
            for &v in &self.graph[task] {
                self.num_dep[v] -= 1;
                if self.num_dep[v] == 0 {
                    self.ready_tasks.push(v);
                }
            }


            self.current_task[p] = None;
            let complete_time = self.step - self.task_begin[task];
            self.complete_tasks[p].push((task, complete_time));
            self.free_members.push_back(p);

            for i in 0..self.k {
                self.skill_lb[p][i] = self.skill_lb[p][i].max(self.d[task][i] as f64 - complete_time as f64);
            }

            output_estimation(p, &self.skill_lb[p]);
        }

        self.step += 1;
    }
}


fn main() {
    let mut source = proconio::source::line::LineSource::new(std::io::BufReader::new(std::io::stdin()));
    proconio::input!{
        from &mut source,
        n: usize,
        m: usize,
        k: usize,
        r: usize,
        d: [[u64; k]; n],
        es: [(Usize1, Usize1); r],
    }

    let mut state = State::new(n, m, k, r, d, es);

    for t in 0.. {
        let assign = state.assign();

        output(&assign);
        if let Some(finish) = input(&mut source) {
            state.finish(&finish);
        } else {
            return;
        }
    }
}

fn output(assign: &Vec<(usize, usize)>) {
    use std::io::Write;
    println!("{} {}", assign.len(), assign.iter().map(|(a, b)| format!("{} {}", a+1, b+1)).collect::<Vec<_>>().join(" "));
    std::io::stdout().flush().ok();
}

fn output_estimation(member: usize, skill: &Vec<f64>) {
    println!("#s {} {}", member+1, skill.iter().map(|x| (*x as u64).to_string()).collect::<Vec<_>>().join(" "));
}

fn input<S: proconio::source::Source<R>, R: BufRead>(mut source: S) -> Option<Vec<usize>> {
    proconio::input!{ from &mut source, n: i64 };

    if n < 0 {
        None
    } else if n == 0 {
        Some(vec![])
    } else {
        proconio::input! {
            from &mut source,
            f: [Usize1; n as usize],
        }
        Some(f)
    }
}