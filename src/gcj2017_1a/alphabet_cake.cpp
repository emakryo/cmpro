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

void rec(vector<string> &x, int x0, int x1, int y0, int y1){
    int m = 0;
    set<int> px, py;
    for(int i=x0; i<x1; i++){
        for(int j=y0; j<y1; j++){
            if(x[i][j]!='?'){
                m++;
                px.insert(i);
                py.insert(j);
            }
        }
    }

    if(m==1){
        for(int i=x0; i<x1; i++){
            for(int j=y0; j<y1; j++){
                x[i][j] = x[*px.begin()][*py.begin()];
            }
        }
    } else {
        if(py.size()>1) {
            int t = *py.begin();
            rec(x, x0, x1, y0, t+1);
            rec(x, x0, x1, t+1, y1);
        } else {
            int t = *px.begin();
            rec(x, x0, t+1, y0, y1);
            rec(x, t+1, x1, y0, y1);
        }
    }
}

void solve(){
    int r, c; cin >> r >> c;
    vector<string> x(r);
    cin >> x;
    rec(x, 0, r, 0, c);

    for(int i=0; i<r; i++){
        cout << x[i] << endl;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t; cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ":" <<endl;
        solve();
    }
    return 0;
}