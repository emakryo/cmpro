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
    vector<int> x(n);
    cin >> x;

    vector<int> primes = Prime(50).primes;
    ll ans = 1e18;
    dbg(primes.size());

    for(int s=1; s<1<<15; s++){
        bool ok = true;
        for(int i=0; i<n; i++){
            bool ok2 = false;
            for(int k=0; k<15; k++){
                if((s>>k&1) && x[i]%primes[k]==0){
                    ok2 = true;
                }
            }

            ok = ok && ok2;
        }
        ll y = 1;
        for(int k=0; k<15; k++){
            if(s>>k&1) y *= primes[k];
        }
        if(ok) ans = min(ans, y);
    }

    cout << ans << endl;
    return 0;
}
