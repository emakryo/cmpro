#include<iostream>
#include<vector>
#include<map>
#include<cmath>
using namespace std;
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

vector<vector<int>> divisors;
void get_divisors(int maximum){
	divisors = vector<vector<int>>(maximum+1);
	for(int i=2; 2*i<divisors.size(); i++){
		for(int j=2*i; j<divisors.size(); j+=i) divisors[j].push_back(i);
	}
}

int main(){
	get_primes(10000000);
	for(int i=0; i<20; i++) cout << primes[primes.size()-1-i] << endl;
	for(auto p: get_factors(9999995)) cout << p.first << " " << p.second << endl;
}

