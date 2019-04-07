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
int N;

int main(){
	cin >> N;

	vector<int> primes(1, 2);
	for(int n=3; n<100; n++){
		bool f = true;
		for(int i=0; i<primes.size(); i++){
			if(n%primes[i]==0){
				f=false;
				break;
			}
		}
		if(f) primes.push_back(n);
	}

	vector<int> n_primes(primes.size());
	for(int i=2; i<=N; i++){
		int n = i;
		int k = 0;
		while(n > 1){
			if(n % primes[k] == 0){
				n_primes[k] += 1;
				n /= primes[k];
			} else {
				k++;
			}
		}
	}

	//for(int i=0; i<n_primes.size(); i++) cout << primes[i] << " " << n_primes[i] << endl;

	map<int, int> cnt;
	for(int a: {2, 4, 14, 24, 74}){
		cnt[a] = 0;
		for(int i=0; i<n_primes.size(); i++){
			if(n_primes[i]>=a) cnt[a]++;
		}
	}

	int ans = 0;
	// 75
	ans += cnt[74];
	// 3*25
	ans += cnt[24]*max(0, cnt[2]-1);
	// 5*15
	ans += cnt[14]*max(0, cnt[4]-1);
	// 3*5*5
	ans += cnt[4]*(cnt[4]-1)/2*max(0, cnt[2]-2);

	cout << ans << endl;

	return 0;
}
