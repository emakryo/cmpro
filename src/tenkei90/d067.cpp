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
    string n;
    cin >> n;
    int k;
    cin >> k;

    ll x = 0;
    for(char c: n){
        x = 8*x+(c-'0');
    }
    if(x==0){
        cout << 0 << endl;
        return 0;
    }

    for(int i=0; i<k; i++){
        ll y = 0;
        ll d = 1;
        while(x>0){
            if(x%9==8){
                y += 5*d;
            } else {
                y += x%9*d;
            }
            x /= 9;
            d *= 8;
        }
        x = y;
    }

    string ans;
    while(x>0){
        ans += '0'+x%8;
        x /= 8;
    }
    reverse(ans.begin(), ans.end());

    cout << ans << endl;
    return 0;
}