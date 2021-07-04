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

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n);
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }

    int ans = 0;
    for(int i=0; i<n; i++){
        vector<bool> visit(n);
        visit[i] = true;
        queue<int> que;
        que.push(i);

        while(que.size()){
            int u = que.front();
            que.pop();
            
            for(int v: g[u]){
                if(!visit[v]){
                    visit[v] = true;
                    que.push(v);
                }
            }
        }

        for(int u=0; u<n; u++){
            if(visit[u]) ans++;
        }
    }

    cout << ans << endl;
    return 0;
}