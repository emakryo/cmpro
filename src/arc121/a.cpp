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
    vector<pair<ll, int>> x(n), y(n);
    for(int i=0; i<n; i++){
        cin >> x[i].first >> y[i].first;
        x[i].second = y[i].second = i;
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    map<pair<int, int>, ll> m;

    pair<int,int> p;
    p = {x[n-1].second, x[0].second};
    if(p.first>p.second) swap(p.first, p.second);
    m[p] = max(m[p], x[n-1].first - x[0].first);

    p = {x[n-2].second, x[0].second};
    if(p.first>p.second) swap(p.first, p.second);
    m[p] = max(m[p], x[n-2].first - x[0].first);

    p = {x[n-1].second, x[1].second};
    if(p.first>p.second) swap(p.first, p.second);
    m[p] = max(m[p], x[n-1].first - x[1].first);

    p = {y[n-1].second, y[0].second};
    if(p.first>p.second) swap(p.first, p.second);
    m[p] = max(m[p], y[n-1].first - y[0].first);

    p = {y[n-2].second, y[0].second};
    if(p.first>p.second) swap(p.first, p.second);
    m[p] = max(m[p], y[n-2].first - y[0].first);

    p = {y[n-1].second, y[1].second};
    if(p.first>p.second) swap(p.first, p.second);
    m[p] = max(m[p], y[n-1].first - y[1].first);

    vector<ll> a;
    for(auto mi: m){
        dbg(mi.first.first, mi.first.second, mi.second);
        a.push_back(mi.second);
    }
    sort(a.rbegin(), a.rend());

    cout << a[1] << endl;

    return 0;
}