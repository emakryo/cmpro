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
vector<ll> x;

void solve_easy() {
    int ans = 0;
    ll last = 0;
    for(int i=0; i<n; i++){
        if(last < x[i]){
            last = x[i];
            continue;
        }

        string a = to_string(last);
        string b = to_string(x[i]);

        ll d = 1;
        for(int k=0; k<a.size()-b.size(); k++) d*=10;
        bool done = false;
        for(ll j=0; j<d; j++){
            string c = to_string(j);
            while(c.size()<a.size()-b.size()){
                c = "0" + c;
            }
            ll z = stoi(b+c);
            if(z>last){
                last = z;
                ans += c.size();
                done = true;
                break;
            }
        }

        if(!done){
            int p = a.size()-b.size()+1;
            for(int k=0; k<p; k++){
                b += '0';
            }
            ans += p;
            last = stoi(b);
        }

        dbg(i, ans, last);
    }
    cout << ans << endl;
}

void solve() {
    cin >> n;
    vector<string> xs(n);
    cin >> xs;
    // for(int i=0; i<n; i++) xs[i] = to_string(x[i]);

    dbg(xs);

    int ans = 0;
    string last;
    for(int i=0; i<n; i++){
        if(last.size() < xs[i].size()){
            last = xs[i];
            continue;
        } else if(last.size() == xs[i].size()){
            if(last < xs[i]){
                last = xs[i];
                continue;
            }
        }

        int p = last.size() - xs[i].size();
        string a = xs[i] + string(p, '0');
        string b = xs[i] + string(p, '9');
        // dbg(last, a, b);

        if(last < a){
            last = a;
        } else if(last < b) {
            last = xs[i] + last.substr(xs[i].size(), p);
            int k = last.size()-1;
            while(k>0){
                if(last[k]=='9'){
                    last[k]='0';
                    k--;
                } else {
                    last[k]++;
                    break;
                }
            }
        } else {
            p++;
            last = xs[i] + string(p, '0');
        }
        ans += p;

        // dbg(p, last);
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    mt19937 engine;
    engine.seed(0);
    uniform_int_distribution dist(1, 100);
    int t; cin >> t;
    for(int i=0; i<t; i++){
        cout << "Case #" << i+1 << ": ";
        // cin >> n;
        // x.assign(n, 0);
        // cin >> x;

        // n = 10;
        // x.assign(n, 0);
        // for(int i=0; i<n; i++){
        //     x[i] = dist(engine);
        // }
        // cout << x << endl;

        solve();
        // solve_easy();
    }
    return 0;
}