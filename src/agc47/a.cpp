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

#include<bits/stdc++.h>

struct Prime {
    std::vector<bool> sieve;
    std::vector<int> primes;

    // Keep primes up to n_max
    Prime(int n_max) {
        sieve = std::vector<bool>(n_max+1);
        sieve[0]=sieve[1]=false;
        for(int i=2; i<sieve.size(); i++) sieve[i]=true;
        for(int j=4; j<sieve.size(); j+=2) sieve[j]=false;
        for(int i=3; 2*i<sieve.size(); i++){
            if(!sieve[i]) continue;
            for(int j=2*i; j<sieve.size(); j+=i) sieve[j] = false;
        }
        for(int i=2; i<sieve.size(); i++){
            if(sieve[i]) primes.push_back(i);
        }
    }

    std::map<long long, int> factorize(long long x) {
        std::map<long long, int> fs;
        for(int p: primes){
            if(p*p>x) break;
            while(x%p==0){
                fs[p]++;
                x /= p;
            }
        }
        if(x>1) fs[x]++;
        return fs;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n; cin >> n;
    vector<ll> a(n);
    for(int i=0; i<n; i++){
        string x; cin >> x;
        int p = x.find('.');
        if(p == string::npos){
            stringstream ss(x);
            ss >> a[i];
            a[i] *= 1e9;
        } else {
            stringstream ss(x.substr(0, p));
            ss >> a[i];
            a[i] *= 1e9;
            string f = x.substr(p+1);
            while(f.size()<9) f+='0';
            stringstream ss1(f);
            ll fl;
            ss1 >> fl;
            a[i] += fl;
        }
    }
    dbg(a);

    vector<vector<ll>> cnt(19, vector<ll>(19));

    for(int i=0; i<n; i++){
        int e2=0, e5=0;
        while(a[i]%2==0){
            a[i]/=2;
            e2++;
        }
        while(a[i]%5==0){
            a[i]/=5;
            e5++;
        }
        cnt[min(e2, 18)][min(e5, 18)]++;
    }

    ll ans = 0;
    for(int i=0; i<19*19; i++){
        if(i/19==0) dbg(cnt[i%19]);
        for(int j=i; j<19*19; j++){
            int e2=i%19, e5=i/19, f2=j%19, f5=j/19;
            if(e2+f2>=18&&e5+f5>=18){
                if(i==j){
                    ans += cnt[e2][e5] * (cnt[e2][e5]-1) / 2;
                } else {
                    ans += cnt[e2][e5] * cnt[f2][f5];
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}