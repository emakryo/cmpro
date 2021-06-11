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

    int n, s;
    cin >> n >> s;

    vector<int> a(n), b(n), c(n);
    for(int i=0; i<n; i++){
        cin >> a[i] >> b[i];
        s -= min(a[i], b[i]);
        c[i] = max(a[i], b[i]) - min(a[i], b[i]);
    }
    if(s<0) {
        cout << "Impossible" << endl;
        return 0;
    }

    vector<int> x(s+1, -1);
    x[0] = 0;
    for(int i=0; i<n; i++){
        for(int j=s-c[i]; j>=0; j--){
            if(x[j]>=0&&x[j+c[i]]<0){
                x[j+c[i]] = i;
            }
        }
    }

    if(x[s]<0){
        cout << "Impossible" << endl;
        return 0;
    }

    int k = s;
    vector<bool> used(n);
    while(k>0){
        used[x[k]] = true;
        k -= c[x[k]];
    }
    string ans;
    for(int i=0; i<n; i++){
        ans += (used[i]==(a[i]>b[i])?'A':'B');
    }
    cout << ans << endl;
    return 0;
}