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

    int n;
    cin >> n;

    vector<ll> ar, ag, ab;
    for(int i=0; i<2*n; i++){
        ll a;
        string c;
        cin >> a >> c;

        if(c=="R") ar.push_back(a);
        if(c=="G") ag.push_back(a);
        if(c=="B") ab.push_back(a);
    }

    sort(ar.begin(), ar.end());
    sort(ag.begin(), ag.end());
    sort(ab.begin(), ab.end());

    dbg(ar.size(), ag. size(), ab.size());

    vector<ll> x, y, z;
    if(ar.size()%2==0&&ag.size()%2==0&&ab.size()%2==0){
        cout << 0 << endl;
        return 0;
    } else if(ar.size()%2==0){
        x = ag;
        y = ab;
        z = ar;
    } else if(ag.size()%2==0){
        x = ar;
        y = ab;
        z = ag;
    } else if(ab.size()%2==0){
        x = ar;
        y = ag;
        z = ab;
    }

    dbg(x);
    dbg(y);
    dbg(z);

    ll ans = 1e18;
    for(ll xi: x){
        int i = lower_bound(y.begin(), y.end(), xi) - y.begin();

        if(i<y.size()){
            ans = min(ans, abs(y[i]-xi));
        }
        if(i>0){
            ans = min(ans, abs(y[i-1]-xi));
        }
    }

    if(z.size()==0){
        cout << ans << endl;
        return 0;
    }

    vector<pair<ll, int>> dx(z.size(), {1e18, 0}), dy(z.size(), {1e18, 0});
    for(int i=0; i<z.size(); i++){
        int j = lower_bound(y.begin(), y.end(), z[i]) - y.begin();

        if(j<y.size()){
            dy[i].first = min(dy[i].first, abs(y[j]-z[i]));
        }
        if(j>0){
            dy[i].first = min(dy[i].first, abs(y[j-1]-z[i]));
        }

        int k = lower_bound(x.begin(), x.end(), z[i]) - x.begin();

        if(k<x.size()){
            dx[i].first = min(dx[i].first, abs(x[k]-z[i]));
        }
        if(k>0){
            dx[i].first = min(dx[i].first, abs(x[k-1]-z[i]));
        }

        dy[i].second = dx[i].second = i;
    }

    sort(dx.begin(), dx.end());
    sort(dy.begin(), dy.end());

    if(dx[0].second != dy[0].second){
        ans = min(ans, dx[0].first + dy[0].first);
    } else {
        ans = min(ans, dx[0].first + dy[1].first);
        ans = min(ans, dx[1].first + dy[0].first);
    }

    cout << ans << endl;
    return 0;
}