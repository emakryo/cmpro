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

struct Prime {
	std::vector<bool> sieve;
	std::vector<int> list;

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
			if(sieve[i]) list.push_back(i);
		}
	}

	std::map<long long, int> factors(long long x) {
		std::map<long long, int> fs;
		for(int p: list){
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
	Prime pr(1000005);

	ll n; cin >> n;

	int ans = 0;
	for(int p: pr.list){
		if(n==1) break;
		if(n%p) continue;

		int e = 0;
		while(n%p==0){
			n/=p;
			e++;
		}

		int i=1;
		while(e-i>=0){
			e-=i;
			i++;
			ans++;
		}
	}

	if(n>1) ans++;

	cout << ans << endl;


	return 0;
}
