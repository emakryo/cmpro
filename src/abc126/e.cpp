#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Mmax = 1e5;
int N, M, X[Mmax], Y[Mmax], Z[Mmax];

void dfs(int v, vector<vector<int>> &graph, vector<bool> &visit){
    for(int u: graph[v]){
        if(visit[u]) continue;
        visit[u]=true;
        dfs(u, graph, visit);
    }
}

int main(){
    cin >> N >> M;
    for(int i=0; i<M; i++){
        cin >> X[i] >> Y[i] >> Z[i];
        X[i]--; Y[i]--;
    }

    vector<vector<int>> graph(N);
    for(int i=0; i<M; i++){
        graph[X[i]].push_back(Y[i]);
        graph[Y[i]].push_back(X[i]);
    }

    vector<bool> visit(N, false);
    int ans = 0;
    for(int i=0; i<N; i++){
        if(!visit[i]){
            ans++;
            visit[i]=true;
            dfs(i, graph, visit);
        }
    }

    cout << ans << endl;

    return 0;
}