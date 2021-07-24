pub fn dijkstra(s: usize, g: &Vec<Vec<(usize, i64)>>) -> Vec<i64> {
    let n = g.len();

    let inf = i64::max_value();
    let mut dist = vec![inf; n];
    dist[s] = 0;
    let mut que = std::collections::BinaryHeap::new();
    que.push((0, s));

    while let Some((d, u)) = que.pop() {
        let d = -d;
        if d > dist[u] {
            continue;
        }
        for &(v, w) in &g[u] {
            let d = d + w;
            if d < dist[v] {
                dist[v] = d;
                que.push((-d, v));
            }
        }
    }

    dist
}