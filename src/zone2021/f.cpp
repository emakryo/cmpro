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

    int n, m;
    cin >> n >> m;
    int k=0;
    while(1<<k<n) k++;

    vector<int> a(m);
    cin >> a;

    set<int> sa(a.begin(), a.end());

    vector<int> bs;
    vector<int> xs;
    for(int i=1; i<n; i++){
        if(sa.count(i)) continue;
        int x = i;
        for(int b: bs){
            x = min(x, x^b);
        }
        if(x){
            bs.push_back(x);
            xs.push_back(i);
        }
    }
    dbg(xs);

    if(xs.size() < k){
        cout << -1 << endl;
        return 0;
    }

    vector<int> c(1);
    for(int i=0; i<k; i++){
        int l = c.size();
        for(int j=0; j<l; j++){
            int d = c[j]^xs[i];
            cout << c[j] << " " << d << endl;
            c.push_back(d);
        }
    }

    return 0;
}