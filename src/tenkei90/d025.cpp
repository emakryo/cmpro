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

ll n, b;

int check(vector<int> &v){
    ll p = 1;
    for(int i=0; i<10; i++){
        for(int j=0; j<v[i]; j++) p*=i;
    }
    ll m = b+p;
    if(m>n) return 0;

    vector<int> z(10);
    while(m){
        z[m%10]++;
        m/=10;
    }

    bool ok = true;
    for(int i=0; i<10; i++){
        if(v[i]!=z[i]) ok = false;
    }

    return ok?1:0;
}

ll dfs(int k, vector<int> &v){
    if(reduce(v.begin(), v.end())>11) return 0;
    if(k==10){
        dbg(v);
        return check(v);
    }

    ll ans = 0;
    for(int i=0; i<=10; i++){
        v[k] = i;
        ans += dfs(k+1, v);
    }
    v[k] = 0;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    cin >> n >> b;

    vector<int> v(10);
    cout << dfs(0, v) << endl;
    return 0;
}