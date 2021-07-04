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
    vector<ll> b(n);
    cin >> b;

    if(n==1){
        cout << 0 << endl;
        return 0;
    } else if(n==2){
        cout << (b[0]==b[1]?0:1) << endl;
        return 0;
    }

    vector<bool> ok(n);
    for(int i=0; i<n; i++){
        ok[i] = b[(i+1)%n] % gcd(b[i], b[(i+2)%n]) == 0;
    }

    dbg(ok);

    int ans = 1e9;
    for(int k=0; k<3; k++){
        vector<bool> okk(ok);
        int a = 0;
        dbg(k, okk[k]);
        if(!okk[k]){
            a++;
            okk[k] = okk[(k-1+n)%n] = okk[(k-2+n)%n] = true;
        }

        for(int i=k+1; i<n+k; i++){
            if(!okk[i%n]){
                a++;
                okk[(i+1)%n] = okk[(i+2)%n] = true;
            }
        }
        dbg(k, a);
        ans = min(ans, a);
    }
    cout << ans << endl;

    return 0;
}