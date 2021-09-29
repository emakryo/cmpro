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

pair<int, int> dfs(int u, vector<bool> &visit, vector<vector<int>> &g) {
    visit[u] = true;
    int x = 1;
    int e = g[u].size();

    for(int v: g[u]) {
        if(visit[v]) continue;
        auto p = dfs(v, visit, g);
        x += p.first;
        e += p.second;
    }

    return {x, e};
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    string a, b;
    cin >> a;
    cin >> b;

    int n = a.size();
    vector<int> ca(26), cb(26);
    vector<vector<int>> g(26);
    for(int i=0; i<n; i++) {
        int u = a[i]-'a';
        int v = b[i]-'a';
        ca[u]++;
        cb[v]++;
        if(u!=v){
            g[u].push_back(v);
        }
    }

    for(int i=0; i<26; i++){
        if(ca[i]!=cb[i]) {
            cout << "NO" << endl;
            return 0;
        }
    }

    vector<bool> visit(26);
    int z = 0;
    for(int i=0; i<26; i++){
        if(visit[i]) continue;
        auto p = dfs(i, visit, g);
        int x = p.first;
        int e = p.second;

        dbg(i, x, e);

        if(x==2&&e==2) z+=1;
        else if(x==2&&e==4) z+=2;
        else if(x==2&&e==6) z+=3;

        else if(x==3&&e==3) z+=2;
        else if(x==3&&e==4) z+=2;
        else if(x==3&&e==5) z+=3;
        else if(x==3&&e==6) z+=3;

        else if(x==4&&e==4) z+=3;
        else if(x==4&&e==5) z+=3;
        else if(x==4&&e==6) z+=3;
        else if(x!=1) {
            cout << "NO" << endl;
            return 0;
        }
    }
    dbg(z);

    if(z<=3&&(z%2==1||*max_element(ca.begin(), ca.end())>=2)){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}