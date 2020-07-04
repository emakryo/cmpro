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
/*
std::vector<bool> sieve;
std::vector<int> primes;

void eratosthenes(int maximum){
	sieve = std::vector<bool>(maximum+1);
	sieve[0]=sieve[1]=false;
	for(int i=2; i<sieve.size(); i++) sieve[i]=true;
	for(int j=4; j<sieve.size(); j+=2) sieve[j]=false;
	for(int i=3; 2*i<sieve.size(); i++){
		if(!sieve[i]) continue;
		for(int j=2*i; j<sieve.size(); j+=i) sieve[j] = false;
	}
}

void get_primes(int maximum){
	if(sieve.size() < maximum) eratosthenes(maximum);
	for(int i=2; i<sieve.size(); i++){
		if(sieve[i]) primes.push_back(i);
	}
}

std::map<long long, int> get_factors(long long x){
	std::map<long long, int> factors;
	for(int p: primes){
		if(p*p>x) break;
		while(x%p==0){
			factors[p]++;
			x /= p;
		}
	}
	if(x>1) factors[x]++;
	return factors;
}
*/

struct Prime {
	std::vector<bool> sieve;
	std::vector<int> list;

	// Keep primes up to n_max
	Prime(int n_max) {
		sieve = std::vector<bool>(n_max+1, true);
		sieve[0] = sieve[1] = false;
		for(int i=4; i<sieve.size(); i+=2) sieve[i] = false;
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

	bool is_prime(int n){
		return sieve[n];
	}
};


/*
int _main(){
	using namespace std;
	get_primes(10000000);
	for(int i=0; i<20; i++) cout << primes[primes.size()-1-i] << endl;
	for(auto p: get_factors(9999995)) cout << p.first << " " << p.second << endl;
	return 0;
}
*/

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;
	Prime pr(10000005);
	int n; cin >> n;

	ll ans = 0;
	for(ll i=1; i<=n; i++){
		ll k = n/i;
		dbg(i, k, i*k*(k+1)/2);
		ans += i * k * (k+1) / 2;
	}

	cout << ans << endl;

	return 0;
}
