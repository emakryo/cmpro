#include<bits/stdc++.h>

struct Prime {
	std::vector<int> sieve;
	std::vector<int> primes;

	// Keep primes up to n_max
	Prime(int n_max) {
		sieve = std::vector<int>(n_max+1);
		for(int i=2; i<sieve.size(); i++){
			if(sieve[i]>0) continue;
			for(int j=2*i; j<sieve.size(); j+=i) sieve[j] = i;
		}
		for(int i=2; i<sieve.size(); i++){
			if(sieve[i]==0) primes.push_back(i);
		}
	}

	std::map<long long, int> factorize(long long x) {
		int m = sieve.size();
		assert(x <= (long long)m * m);
		if(x < m){
			return factorize_fast(x);
		} else {
			return factorize_naive(x);
		}
	}

	std::map<long long, int> factorize_naive(long long x){
		std::map<long long, int> fs;
		for(int p: primes) {
			if(p*p>x) break;
			while(x%p==0) {
				fs[p]++;
			}
		}
		if(x>1) fs[x]++;
		return fs;
	}

	std::map<long long, int> factorize_fast(int x){
		std::map<long long, int> fs;
		while(x > 1) {
			fs[sieve[x]]++;
			x /= sieve[x];
		}
		return fs;
	}
};