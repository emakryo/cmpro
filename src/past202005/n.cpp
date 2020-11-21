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

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int i=0; i<n; i++) a[i] = i+1;

    set<int> s;
    while(q--){
        int t, x, y;
        cin >> t >> x >> y;
        dbg(q, t, x, y);

        if(t == 1){
            x--;
            swap(a[x], a[x+1]);

            if(x-1>=0){
                if(a[x-1]<a[x]) s.erase(x-1);
                else s.insert(x-1);
            }

            if(x+1<n){
                if(a[x]<a[x+1]) s.erase(x);
                else s.insert(x);
            }

            if(x+2<n){
                if(a[x+1]<a[x+2]) s.erase(x+1);
                else s.insert(x+1);
            }
        } else {
            x--; y--;

            while(true){
                auto it = s.lower_bound(x);
                if(it==s.end()) break;
                int i = *it;
                if(i>=y) break;

                while(i<y&&a[i]>a[i+1]){
                    swap(a[i], a[i+1]);
                    if(i-1>=0){
                        if(a[i-1]<a[i]) s.erase(i-1);
                        else s.insert(i-1);
                    }

                    if(i+1<n){
                        if(a[i]<a[i+1]) s.erase(i);
                        else s.insert(i);
                    }

                    if(i+2<n){
                        if(a[i+1]<a[i+2]) s.erase(i+1);
                        else s.insert(i+1);
                    }
                    i++;
                }
            }
        }

        dbg(a);
    }

    cout << a << endl;

    return 0;
}