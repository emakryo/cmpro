#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
    string sep = " ";
    if(v.size()) os << v[0];
    for(int i=1; i<v.size(); i++) os << sep << v[i];
    return os;
}

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
    for(int i=0; i<v.size(); i++) is >> v[i];
    return is;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
    cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

void solve2(){
    string s, e;
    cin >> s >> e;

    if(s=="0"&&e=="0"){
        cout << 0 << endl;
        return;
    }

    vector<int> vs(2), ve(2);
    for(char c: s){
        if(c=='0'){
            vs[vs.size()-1]++;
        } else {
            if(vs[vs.size()-1]){
                vs.push_back(1);
                vs.push_back(0);
            } else{
                vs[vs.size()-2]++;
            }
        }
    }
    if(s == "0"){
        vs = {1, 0};
    }

    for(char c: e){
        if(c=='0'){
            vs[vs.size()-1]++;
        } else {
            if(vs[vs.size()-1]){
                vs.push_back(1);
                vs.push_back(0);
            } else{
                vs[vs.size()-2]++;
            }
        }
    }

    if(e == "0"){
        ve = {1, 0};
    }

    for(int i=0; i<105; i++){
        for(int j=0; j<)
    }

}

void solve(){
    string s, e;
    cin >> s >> e;

    int is = 0, ie = 0;
    for(char c: s){
        is *= 2;
        is += c-'0';
    }
    for(char c: e){
        ie *= 2;
        ie += c-'0';
    }

    vector<vector<int>> g(1<<20);
    for(int i=0; i<(1<<20); i++){
        int j=2*i;
        if(j!=0&&j<(1<<20)){
            g[i].push_back(j);
        }
        j = i;
        int k = 0;
        while(j>0){
            k++;
            j>>=1;
        }
        if(i==0) k=1;

        g[i].push_back(i^((1<<k)-1));
    }

    vector<int> dist(1<<20, 1e9);
    dist[is] = 0;
    queue<pair<int, int>> que;
    que.push({0, is});
    
    while(que.size()){
        int d = que.front().first;
        int u = que.front().second;
        que.pop();

        if(d > dist[u]) continue;

        for(int v: g[u]){
            if(dist[v]>dist[u]+1){
                dist[v] = dist[u]+1;
                dbg(u, v, dist[v]);
                que.push({dist[v], v});
            }
        }
    }
    if(dist[ie]<1e9) cout << dist[ie] << endl;
    else cout << "IMPOSSIBLE" << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t; cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}