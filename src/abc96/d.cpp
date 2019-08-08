#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<bool> sieve;
vector<int> primes;

void eratosthenes(int maximum){
	sieve = vector<bool>(maximum+1);
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

map<int, int> get_factors(int x){
	map<int, int> factors;
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

int main(){
	int N;
	cin >> N;

	get_primes(55555);

	vector<int> ans;
	for(int i=0; i<primes.size(); i++){
		if(primes[i]%5==1) ans.push_back(primes[i]);
	}

	for(int i=0; i<N; i++){
		cout << ans[i] << (i==N-1?'\n':' ');
	}

	return 0;
}
