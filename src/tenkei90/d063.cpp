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

    int h, w;
    cin >> h >> w;
    vector<vector<int>> p(h, vector<int>(w));
    cin >> p;

    int ans = 0;
    for(int s=1; s<(1<<h); s++){
        vector<int> x(h*w+1);
        for(int i=0; i<w; i++){
            bool ok = true;
            int z = -1;
            for(int j=0; j<h; j++){
                if((s>>j&1)==0) continue;
                if(z<0) z = p[j][i];
                else{
                    if(z!=p[j][i]) ok = false;
                }
            }
            if(ok) x[z]++;
        }

        int k = 0;
        for(int j=0; j<h; j++) k+=s>>j&1;
        dbg(s, k);
        dbg(x);
        ans = max(ans, k*(*max_element(x.begin(), x.end())));
    }

    cout << ans << endl;
    return 0;
}