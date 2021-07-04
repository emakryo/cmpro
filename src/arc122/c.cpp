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

ll gcd(ll x, ll y){
    if(y==0) return x;
    return gcd(y, x%y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    ll n;
    cin >> n;
    if(n==1){
        cout << 1 << endl;
        cout << 1 << endl;
        return 0;
    }

    vector<int> ans;
    double gr = (1+sqrt(5))/2;
    for(int i=0; i<100; i++){
        // ll gi = gcd(x, y0-i);
        // dbg(i, y0-i, gi);
        // if(gi<g){
        //     y = y0-i;
        //     g = gi;
        // }
        ll x = n;
        ll y = (ll)(n/gr)-i;
        if(y==0) break;
        vector<int> ans0;
        dbg(x, y);
        while(x>0&&y>0){
            if(x > y){
                x -= y;
                ans0.push_back(3);
            } else {
                y -= x;
                ans0.push_back(4);
            }
            // dbg(x, y);
        }

        while(x>0){
            x--;
            ans0.push_back(1);
        }
        while(y>0){
            y--;
            ans0.push_back(2);
        }

        dbg(ans0.size());

        if(ans.empty()||ans0.size()<ans.size()) {
            ans = ans0;
        }
    }

    cout << ans.size() << endl;
    reverse(ans.begin(), ans.end());
    for(int a: ans){
        cout << a << endl;
    }

    return 0;
}