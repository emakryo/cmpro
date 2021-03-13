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

    int n, k; cin >> n >> k;
    vector<vector<int>> a(n, vector<int>(k));
    for(int i=0; i<n; i++) cin >> a[i];

    int dup = 0;
    int next = 0;
    vector<bool> done(1000000);
    vector<int> last(n);
    for(int i=0; i<n; i++){
        vector<int> fix;
        int p = (k+dup)/n;
        if(i<(k+dup)%n) p++;
        dbg(i, p);
        for(int j=0; j<p; j++){
            if(!done[a[i][j]]){
                fix.push_back(a[i][j]);
                done[a[i][j]] = true;
            } else {
                dup++;
            }
        }
        last[i] = p;

        while(true){
            bool changed = false;
            for(int j=0; j<=i; j++){
                int p = (k+dup)/n;
                if(j<(k+dup)%n) p++;
                dbg(i, j, p, dup);
                for(int l=last[j]; l<p; l++){
                    changed = true;
                    if(!done[a[j][l]]){
                        fix.push_back(a[j][l]);
                        done[a[j][l]] = true;
                    } else {
                        dup++;
                    }
                }
                last[j] = p;
            }
            if(!changed) break;
        }

        sort(fix.begin(), fix.end());
        cout << fix << endl;
    }

    return 0;
}