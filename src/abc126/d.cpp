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
const int Nmax = 1e5;
int N, U[Nmax], V[Nmax];
ll W[Nmax];

void dfs(int v, vector<vector<pair<int, int> > > &graph, vector<int> &ans){
    // cout << v << endl;
    for(auto p: graph[v]){
        if(ans[p.first]>=0) continue;
        if(p.second==0){
            ans[p.first] = ans[v];
        } else {
            ans[p.first] = 1-ans[v];
        }
        dfs(p.first, graph, ans);
    }
}
int main(){
    cin >> N;
    for(int i=0; i<N-1; i++){
        cin >> U[i] >> V[i] >> W[i];
        U[i]--; V[i]--;
    }
    vector<vector<pair<int, int> > > graph(N);
    for(int i=0; i<N-1; i++){
        // cout << U[i] << " " << V[i] << endl;
        graph[U[i]].push_back({V[i], W[i]%2});
        graph[V[i]].push_back({U[i], W[i]%2});
    }
    vector<int> ans(N, -1);

    ans[0] = 0;
    dfs(0, graph, ans);

    for(int i=0; i<N; i++){
        cout << ans[i] << endl;
    }

    return 0;
}