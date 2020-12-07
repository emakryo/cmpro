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

    int n; cin >> n;
    vector<ll> a(n); cin >> a;

    int lb=0, ub=n;
    while(ub-lb>1){
        int x = (lb+ub)/2;
        map<ll, int> count;
        bool ok = true;
        for(int i=1; i<n; i++){
            if(a[i-1]<a[i]) continue;
            auto it = count.rbegin();
            while(it!=count.rend()&&it->first>a[i]){
                int z = it->first;
                it++;
                count.erase(z);
            }

            count[a[i]]++;
            int k = a[i];
            if(x==1){
                if(count[k] >= 1){
                    ok = false;
                    break;
                }
            } else {
                while(k>0&&count[k]==x){
                    count.erase(k);
                    k--;
                    if(k==0){
                        ok=false;
                        break;
                    }
                    count[k]++;
                }
                if(!ok) break;
            }
            // for(auto p: count) {
            //     dbg(x, i, p.first, p.second);
            // }
        }
        // for(auto p: count) {
        //     dbg(x, p.first, p.second);
        // }
        // dbg(x, ok);

        if(ok){
            ub=x;
        } else {
            lb=x;
        }
    }

    cout << ub << endl;
    return 0;
}