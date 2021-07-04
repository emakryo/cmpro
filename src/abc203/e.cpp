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

    ll n;
    int m;
    cin >> n >> m;
    vector<ll> x(m), y(m);

    for(int i=0; i<m; i++) cin >> x[i] >> y[i];

    map<ll, vector<ll>> xy;

    for(int i=0; i<m; i++){
        xy[x[i]].push_back(y[i]);
    }

    set<ll> xs;
    xs.insert(n);
    for(auto &p: xy){
        sort(p.second.begin(), p.second.end());
        set<ll> add, erase;
        for(ll y: p.second){
            erase.insert(y);
            if(xs.count(y-1)){
                add.insert(y);
            }
            if(xs.count(y+1)){
                add.insert(y);
            }
        }
        for(ll y: erase){
            xs.erase(y);
        }

        for(ll y: add){
            xs.insert(y);
        }
    }

    cout << xs.size() << endl;

    return 0;
}