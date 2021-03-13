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

int q(int l, int r){
    cout << "? " << l+1 << " " << r << endl;
    int x;
    cin >> x;
    return x-1;
}

void o(int x){
    cout << "! " << x+1 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int n; cin >> n;

    int s = q(0, n);
    int t = 0;
    if(s==0||(s<n&&(t=q(0, s+1))!=s)){
        int l = s;
        int lb = l+1, ub = n;
        while(ub-lb>1){
            int m = (lb+ub)/2;
            if(q(l, m) == l){
                ub = m;
            } else {
                lb = m;
            }
        }
        o(lb);
    } else {
        int r = s+1;
        int lb = 0, ub = r-1;
        while(ub-lb>1){
            int m = (lb+ub)/2;
            int x = q(m, r);
            dbg(lb, m, ub, x);
            if(x == s){
                lb = m;
            } else {
                ub = m;
            }
        }
        o(lb);
    }
    return 0;
}