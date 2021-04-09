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
    vector<int> a(n);
    cin >> a;

    vector<vector<int>> v(n, vector<int>(1, -1));

    for(int i=0; i<n; i++){
        v[a[i]].push_back(i);
    }

    for(int i=0; i<n; i++){
        v[i].push_back(n);
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<v[i].size()-1; j++){
            dbg(i, v[i][j], v[i][j+1]);
            if(v[i][j+1]-v[i][j]>m){
                cout << i << endl;
                return 0;
            }
        }
    }

    cout << n << endl;
    return 0;
}