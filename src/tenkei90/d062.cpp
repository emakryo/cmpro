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

    int n;
    cin >> n;
    
    vector<int> a(n), b(n);
    for(int i=0; i<n; i++) cin >> a[i] >> b[i];

    vector<vector<int>> g(n);

    vector<int> ans;
    queue<int> que;
    vector<bool> white(n);
    for(int i=0; i<n; i++){
        g[a[i]-1].push_back(i);
        g[b[i]-1].push_back(i);
        if(a[i]-1==i||b[i]-1==i){
            que.push(i);
            white[i] = true;
            ans.push_back(i);
        }
    }


    while(que.size()){
        int v = que.front();
        que.pop();
        for(int u: g[v]){
            if(!white[u]){
                que.push(u);
                ans.push_back(u);
                white[u] = true;
            }
        }
    }

    if(ans.size() < n){
        cout << -1 << endl;
        return 0;
    }

    for(int i=0; i<n; i++){
        cout << ans[n-i-1]+1 << endl;
    }


    return 0;
}