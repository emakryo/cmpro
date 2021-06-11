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

int n;

int query(int i, int j) {
    cout << "M " << i << " " << j << endl;
    int k;
    cin >> k;
    return k;
}

void swap(int i, int j){
    cout << "S " << i << " " << j << endl;
    int k;
    cin >> k;
}

void done(){
    cout << "D" << endl;
    int k;
    cin >> k;
}

void solve(){
    for(int i=0; i<n-1; i++){
        int j = query(i+1, n);
        if(i+1==j) continue;
        swap(i+1, j);
    }
    done();
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t;
    cin >> t >> n;

    for(int i=0; i<t; i++) solve();
    
    return 0;
}