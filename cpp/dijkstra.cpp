#include<bits/stdc++.h>

std::vector<long long> dijkstra(int s, std::vector<std::vector<std::pair<int, long long>>> &g){
    int n = g.size();
    std::vector<long long> dist(n, 1e9);
    dist[s] = 0;
    using Pli = std::pair<long long, int>;
    std::priority_queue<Pli, std::vector<Pli>, std::greater<Pli>> que;
    que.push({0, s});

    while(que.size()){
        int u = que.top().second;
        long long d = que.top().first;
        que.pop();

        if(d > dist[u]) continue;

        for(auto p: g[u]){
            int v = p.first;
            long long dv = dist[u] + p.second;
            if(dv < dist[v]){
                dist[v] = dv;
                que.push({dv, v});
            }
        }
    }

    return dist;
}
