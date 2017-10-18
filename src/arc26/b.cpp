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

int main(){
	ll N, N0;
	cin >> N;
	N0 = N;

	vector<ll> primes;
	vector<int> factors(primes.size());

	for(int n=2; n<=1e5; n++){
		bool is_prime = true;
		for(int i=0; i<primes.size(); i++){
			if(n%primes[i]==0){
				is_prime = false;
				break;
			}
		}
		if(is_prime){
			primes.push_back(n);
			int f = 0;
			while(N%n == 0){
				f++;
				N /= n;
			}
			factors.push_back(f);
		}
	}

	if(N > 1){
		primes.push_back(N);
		factors.push_back(1);
	}

	//for(int i=0; i<primes.size(); i++){
	//	if(factors[i] > 0){
	//		cout << primes[i] << " " << factors[i] << endl;
	//	}
	//}

	ll sum = 1;

	for(int i=0; i<primes.size(); i++){
		if(factors[i]==0) continue;

		sum *= (pow(primes[i], factors[i]+1)-1) / (primes[i]-1);
	}

	sum -= N0;

	//cout << sum << endl;

	if(sum == N0){
		cout << "Perfect" << endl;
	}
	else if(sum < N0){
		cout << "Deficient" << endl;
	}
	else{
		cout << "Abundant" << endl;
	}

	return 0;
}
