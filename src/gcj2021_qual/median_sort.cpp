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
void debug_(){ cerr << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
    cerr << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

vector<int> idx;

int query(int i, int j, int k){
    cout << i << " " << j << " " << k << endl;
    int r;
    cin >> r;

    dbg("q", i, j, k, "->", r);
    if(r == i) return 0;
    else if(r == j) return 1;
    else if(r == k) return 2;
    else exit(1);
}

void rec(int begin, int end) {
    if(end-begin<2) return;

    vector<int> l, m, r;
    int p = idx[begin], q = idx[begin+1];
    dbg("&", begin, end);
    dbg(">", idx);
    dbg("-", p, q);
    for(int i=begin+2; i<end; i++){
        int a = query(p, q, idx[i]);
        if(a==0){
            l.push_back(idx[i]);
        } else if(a==1){
            r.push_back(idx[i]);
        } else {
            m.push_back(idx[i]);
        }
    }
    dbg("l", l);
    dbg("m", m);
    dbg("r", r);

    int b = begin;
    for(int x: l){
        idx[b++] = x;
    }
    rec(b-l.size(), b);
    idx[b++] = p;

    for(int x: m){
        idx[b++] = x;
    }
    rec(b-m.size(), b);
    idx[b++] = q;

    for(int x: r){
        idx[b++] = x;
    }
    rec(b-r.size(), b);

    if(l.size()>=2){
        int a = query(idx[begin], idx[begin+l.size()-1], p);
        if(a==0){
            reverse(idx.begin()+begin, idx.begin()+begin+l.size());
        } else if(a==2){
            dbg("e1");
            assert(false);
        }
    }

    if(m.size()>=2){
        int a = query(idx[begin+l.size()+1], idx[begin+l.size()+m.size()], q);
        if(a==0){
            int b = begin+l.size()+1;
            reverse(idx.begin()+b, idx.begin()+b+m.size());
        } else if(a==2){
            dbg("e2");
            assert(false);
        }
    }

    if(r.size()>=2){
        int b = begin+l.size()+m.size()+1;
        int a = query(q, idx[b+1], idx[b+r.size()]);
        if(a==2){
            reverse(idx.begin()+b+1, idx.begin()+b+1+r.size());
        } else if(a==0){
            dbg("e3");
            assert(false);
        }
    }
}

void solve() {
    for(int i=0; i<idx.size(); i++){
        idx[i] = i+1;
    }

    rec(0, idx.size());

    dbg("a", idx);
    cout << idx << endl;
 
    int r;
    cin >> r;
    if(r!=1) exit(1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;

    int t, n, q;
    cin >> t >> n >> q;

    idx.assign(n, 0);

    for(int i=0; i<t; i++) solve();

    return 0;
}