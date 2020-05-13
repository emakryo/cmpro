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
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

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

int _main(){
	using namespace std;
	get_primes(10000000);
	for(int i=0; i<20; i++) cout << primes[primes.size()-1-i] << endl;
	for(auto p: get_factors(9999995)) cout << p.first << " " << p.second << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	get_primes(200005);
	int n; cin >> n;
	vector<int> a(n);
	for(int i=0; i<n; i++) cin >> a[i];

	map<int, vector<int>> cnt;
	for(int i=0; i<n; i++){
		for(int p: primes){
			if(p*p>a[i]) break;
			int k=0;
			while(a[i]%p==0){
				a[i]/=p;
				k++;
			}
			if(k>0) cnt[p].push_back(k);
		}
		if(a[i]>1) cnt[a[i]].push_back(1);
	}

	ll ans = 1;
	for(auto p: cnt){
		sort(p.second.begin(), p.second.end());
		int k = 0;
		if(p.second.size()==n){
			k=max(p.second[0],p.second[1]);
		} else if(p.second.size()==n-1){
			k=p.second[0];
		}
		dbg(k, p.first);
		while(k){
			ans *= p.first;
			k--;
		}
	}
	cout << ans << endl;
	return 0;
}
