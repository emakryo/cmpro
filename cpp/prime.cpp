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