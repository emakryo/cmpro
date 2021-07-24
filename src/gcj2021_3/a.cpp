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

ll solve_easy(string s){
    vector<int> a;
    for(char c: s) a.push_back(c-'0');
    sort(a.begin(), a.end());

    ll ans = 8e18;
    do {
        ll x=0, y=0;
        bool ok = true;
        for(int i=0; i<a.size()/2; i++){
            if(x==0&&a[i]==0) ok = false;
            x=10*x+a[i];
        }
        for(int i=a.size()/2; i<a.size(); i++){
            if(y==0&&a[i]==0) ok = false;
            y=10*y+a[i];
        }
        if(ok&&abs(x-y)<ans) dbg(x, y);
        if(ok) ans = min(ans, abs(x-y));
    } while(next_permutation(a.begin(), a.end()));

    return ans;
}

ll solve_hard(string s){
    vector<int> a;
    for(char c: s) a.push_back(c-'0');
    sort(a.begin(), a.end());
    vector<int> c(10);
    for(int i=0; i<a.size(); i++){
        c[a[i]]++;
    }

    if(s.size()%2){
        ll x = 0, y = 0;
        int k;
        for(int i=0; i<a.size(); i++){
            if(a[i]!=0){
                x = a[i];
                k = i;
                break;
            }
        }

        vector<int> b;
        for(int i=0; i<a.size(); i++){
            if(i==k) continue;
            b.push_back(a[i]);
        }

        for(int i=0; i<b.size()/2; i++){
            x = 10*x+b[i];
            y = 10*y+b[b.size()-i-1];
        }
        return abs(x-y);
    } else {
        vector<int> p;
        for(int i=0; i<a.size()-1; i++){
            if(a[i]==a[i+1]){
                p.push_back(a[i]);
                i++;
            }
        }

        ll ans = 1LL<<62;

        for(int s=0; s<(1<<p.size()); s++){
            vector<int> cc(c);
            bool ok = s==0;
            for(int i=0; i<p.size(); i++){
                if(s>>i&1){
                    cc[p[i]]-=2;
                    if(p[i]>0) ok = true;
                }
            }
            if(!ok) continue;

            vector<int> xs;
            for(int i=0; i<10; i++){
                for(int k=0; k<cc[i]; k++) xs.push_back(i);
            }
            int n = xs.size();

            for(int i=0; i<n-1; i++){
                if(s==0&&(xs[i+1]==0||xs[i]==0)) continue;
                ll x = xs[i+1], y = xs[i];
                int k=0;
                for(int j=0; j<n/2-1; j++){
                    while(k==i||k==i+1)k++;
                    x = 10*x + xs[k];
                    k++;
                }
                k=n-1;
                for(int j=0; j<n/2-1; j++){
                    while(k==i||k==i+1)k--;
                    y = 10*y + xs[k];
                    k--;
                }
                ans = min(ans, abs(x-y));
                dbg(xs, x, y);
            }
        }
        return ans;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    // string s = "2039482039";
    // string s = "9013";
    // string s = "002339";
    // string s = "999710";
    // dbg(solve_easy(s));
    // dbg(solve_hard(s));
    // return 0;

    // for(int i=0; i<10000000; i++){
    //     string s = to_string(i);
    //     ll e = solve_easy(s);
    //     ll h = solve_hard(s);
    //     if(e!=h) {
    //         cout << i << " " << e << " " << h << " " << endl;
    //     }
    // }
    // return 0;


    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        cout<<"Case #" << i+1 << ": ";
        string s;
        cin >> s;
        // cout << solve_hard(s) << ' ' << solve_easy(s) << endl;
        cout << solve_hard(s) << endl;
    }
    return 0;
}