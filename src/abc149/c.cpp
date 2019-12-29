#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
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

/*
int main(){
	using namespace std;
	get_primes(10000000);
	for(int i=0; i<20; i++) cout << primes[primes.size()-1-i] << endl;
	for(auto p: get_factors(9999995)) cout << p.first << " " << p.second << endl;
}
*/

int main(){
	get_primes(200000);
	//cout << primes[0] << " " << primes[primes.size()-1] << endl;;

	int x;
	cin >> x;
	for(int i=0; i<primes.size(); i++){
		if(primes[i]<x) continue;
		cout << primes[i] << endl;
		break;
	}

	return 0;
}
