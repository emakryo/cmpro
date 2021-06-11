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

void solve(){
    int r, c, f, s;
    cin >> r >> c >> f >> s;
    vector<string> a(r), b(r);
    cin >> a;
    cin >> b;

    assert(f==1&&s==1);

    vector<int> dp(1<<c, 1e9);
    dp[0] = 0;
    for(int i=0; i<r; i++){
        vector<int> next(1<<c, 1e9);
        for(int s=0; s<(1<<c); s++){
            int si = ((1<<c)-1)^s;
            for(int t=si;; t=si&(t-1)){
                int p = 0;

                for(int k=0; k<c; k++){
                    if((si>>k&1)==0) p++;

                    if((t>>k&1)&&(i<r-1)){
                        if(a[i][k]!=b[i+1][k]||a[i+1][k]!=b[i][k]){
                            p=1e9;
                        }
                    }
                }

                for(int k=0; k<c; k++){
                    if((si>>k&1)==0) continue;
                    if(t>>k&1) continue;
                    if(k<c-1&&((si>>(k+1)&1))&&a[i][k]!=b[i][k]&&a[i][k+1]==b[i][k]&&a[i][k]==b[i][k+1]){
                        p++;
                        k++;
                    } else if(a[i][k]!=b[i][k]){
                        p++;
                    }
                }

                if(dp[s]<1e9) dbg(i, s, t, dp[s]+p);
                next[t] = min(next[t], dp[s]+p);
                if(t==0) break;
            }
        }

        dp = next;
    }

    cout << dp[0] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t; cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}