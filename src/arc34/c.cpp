#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const ll P = 1e9+7;
const int Xmax = 100000;

int main(){
	ll A, B;
	cin >> A >> B;

	vector<int> primes;
	primes.push_back(2);
	vector<bool> is_composit(Xmax);
	for(ll i=4; i<Xmax; i+=2) is_composit[i] = true;
	for(ll i=3; i<Xmax; i+=2){
		if(!is_composit[i]){
			primes.push_back(i);
			for(ll j=i*i; j<Xmax; j+=i) is_composit[j] = true;
		}
	}

	vector<int> factors(primes.size());

	for(ll x=B+1; x<=A; x++){
		ll y = x;
		for(int i=0; i<primes.size(); i++){
			int p = primes[i];
			if(y < p) break;
			while(y%p==0){
				factors[i]++;
				y /= p;
			}
		}
		if(y > 1){
			primes.push_back(y);
			factors.push_back(1);
		}
	}

	ll ans = 1;
	for(int f : factors){
		ans = (ans * (f+1)) % P;
	}

	cout << ans << endl;

	return 0;
}
