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

    vector<ll> value;
    ll x;
    while(cin >> x) value.push_back(x);
    int np = 25;

    ll invalid;
    for(int i=np; i<value.size(); i++){
        bool ok = false;
        for(int j=i-np; j<i; j++){
            for(int k=j+1; k<i; k++){
                if(value[j]+value[k]==value[i]){
                    // dbg(value[i], value[j], value[k], i, j, k, i-j, i-k);
                    ok=true;
                }
            }
        }
        if(!ok){
            invalid = value[i];
            break;
        }
    }

    for(int i=0; i<value.size(); i++){
        ll sum = value[i];
        ll vmin = sum;
        ll vmax = sum;
        for(int j=i+1; j<value.size(); j++){
            sum+=value[j];
            vmin = min(vmin, value[j]);
            vmax = max(vmax, value[j]);
            if(sum==invalid){
                cout << vmin+vmax << endl;
                return 0;
            }
        }
    }
    
    return 0;
}