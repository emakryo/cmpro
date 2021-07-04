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
    ll x, y;
    cin >> x >> y;

    if(y<=x){
        cout << x-y << endl;
        return 0;
    }

    ll ans = y-x;
    map<ll, int> dp;
    queue<ll> que;
    dp[y] = 0;
    que.push(y);

    while(que.size()){
        ll z = que.front();
        que.pop();
        dbg(z, dp[z]);
        ans = min(ans, abs(x-z)+dp[z]);
        if(z < x){
            continue;
        }

        for(int i=-2; i<=2; i++){
            ll w = z+i;
            if(w%2==0){
                if(dp.count(w/2)){
                    int k = dp[z]+abs(i)+1;
                    if(k<dp[w/2]){
                        dp[w/2] = k;
                        que.push(w/2);
                    }
                } else {
                    dp[w/2] = dp[z]+abs(i)+1;
                    que.push(w/2);
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}