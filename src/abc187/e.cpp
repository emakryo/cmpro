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

ll dfs(int u, int p, vector<vector<pair<int, int>>> &graph, vector<int> &a, vector<int> &b, vector<ll> &r, vector<ll> &s, vector<ll> &ans){
    ll x = 0;
    for(auto pa: graph[u]){
        int v = pa.first;
        int e = pa.second;
        if(v==p) continue;
        if(a[e]==u){
            ans[v] = ans[u] + s[e]-r[e];
        } else {
            ans[v] = ans[u] + r[e]-s[e];
        }

        x += dfs(v, u, graph, a, b, r, s, ans);

        if(a[e]==u) x+=r[e];
        else x+=s[e];
    }

    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n; cin >> n;
    vector<int> a(n-1), b(n-1);
    vector<vector<pair<int, int>>> graph(n);
    for(int i=0; i<n-1; i++){
        cin >> a[i] >> b[i];
        a[i]--; b[i]--;
        graph[a[i]].push_back({b[i], i});
        graph[b[i]].push_back({a[i], i});
        
    }

    int q; cin >> q;
    vector<ll> r(n), s(n);
    for(int i=0; i<q; i++){
        int t, e;
        ll x;
        cin >> t >> e >> x;
        e--;
        if(t==1) r[e] += x;
        else s[e] += x;
    }

    vector<ll> ans(n);

    ll x0 = dfs(0, -1, graph, a, b, r, s, ans);
    dbg(x0);
    dbg(ans);

    for(int i=0; i<n; i++){
        cout << x0+ans[i] << endl;
    }

    return 0;
}