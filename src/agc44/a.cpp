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

ll get(map<ll, ll> &dp, ll k) {
    if(dp.count(k)){
        return dp[k];
    } else {
        return 1e18;
    }
}

void solve(){
    ll n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    map<ll, ll> dp;
    priority_queue<ll> que;
    que.push(n);
    dp[n] = 0;
    while(que.top()>0){
        ll x = que.top();
        que.pop();
        while(que.size()&&que.top()==x) que.pop();

        ll v = get(dp, x);
        dbg(x, v);

        dp[x/2] = min(get(dp, x/2), v+a+d*(x-x/2*2));
        dp[x/2+1] = min(get(dp, x/2+1), v+a+d*((x+2)/2*2-x));
        dp[x/3] = min(get(dp, x/3), v+b+d*(x-x/3*3));
        dp[x/3+1] = min(get(dp, x/3+1), v+b+d*((x+3)/3*3-x));
        dp[x/5] = min(get(dp, x/5), v+c+d*(x-x/5*5));
        dp[x/5+1] = min(get(dp, x/5+1), v+c+d*((x+5)/5*5-x));

        que.push(x/2);
        if(x/2+1<x) que.push(x/2+1);
        que.push(x/3);
        if(x/3+1<x) que.push(x/3+1);
        que.push(x/5);
        if(x/5+1<x) que.push(x/5+1);
    }

    ll ans = 1e18;
    for(auto p: dp){
        if(p.first > 1e18/d) break;
         ans = min(ans, p.second+p.first*d);
    }

    cout << ans << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t; cin >> t;
    for(int i=0; i<t; i++) solve();

    return 0;
}