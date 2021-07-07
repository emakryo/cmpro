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

    ll a, b;
    cin >> a >> b;

    vector<bool> sieve(73);
    for(int i=2; i<73; i++){
        if(sieve[i]) continue;
        for(int j=2; i*j<73; j++){
            sieve[i*j]=true;
        }
    }
    vector<int> primes;
    for(int i=2; i<73; i++){
        if(!sieve[i]) primes.push_back(i);
    }

    vector<ll> dp(1<<primes.size());
    dp[0] = 1;

    for(ll x=a; x<=b; x++){
        vector<ll> next(dp);
        ll p = 0;
        for(int i=0; i<primes.size(); i++){
            if(x%primes[i]==0) p += 1<<i;
        }
        for(int i=0; i<(1<<primes.size()); i++){
            if(i&p) continue;
            next[i|p] += dp[i];
        }

        dp = next;
    }

    cout << reduce(dp.begin(), dp.end()) << endl;



    return 0;
}