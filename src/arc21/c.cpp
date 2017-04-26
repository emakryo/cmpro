#include<iostream>
#include<iomanip>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 100000;
ll K, N;
ll A[Nmax], D[Nmax];

int main(){
	cin >> K >> N;
	for(int i=0; i<N; i++) cin >> A[i] >> D[i];

	ll lb = 0, ub = 1e15;
	while(ub-lb > 1){
		ll middle = (lb+ub)/2;
		ll sum = 0;
		for(int i=0; i<N; i++){
			if(middle < A[i]) continue;
			sum += (middle-A[i])/D[i] + ((middle-A[i])%D[i] ? 1 : 0);
		}
		if(sum <= K) lb = middle;
		else ub = middle;
	}

	ll ans = 0;
	for(int i=0; i<N; i++){
		if(lb < A[i]) continue;
		ll k = (lb-A[i])/D[i] + ((lb-A[i])%D[i] ? 1 : 0);
		ans += A[i]*k + (k%2==0 ? (k/2)*(k-1) : k*((k-1)/2))*D[i];
		A[i] += k*D[i];
		K -= k;
		//cout << k << " " << A[i] << endl;
	}
	//cout << lb << " " << K << endl;
	//cout << ans << endl;

	sort(A, A+N);
	for(int i=0; i<K; i++) ans += A[i];

	cout << ans << endl;

	return 0;
}
