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
const int Nmax = 5000;
int N,K;
ll A[Nmax];

bool cond(int n){
	vector<bool> vec(K);
	vec[K-1] = true;
	for(int j=0; j<N; j++){
		if(j==n) continue;
		for(int k=0; k<K; k++){
			if(k+A[j]<K) vec[k] = vec[k] || vec[k+A[j]];
		}
	}

	bool ok = true;
	for(int k=0; k<min(A[n], (ll)K); k++){
		ok = ok && !vec[k];
	}
	return ok;
}

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> A[i];

	sort(A, A+N);

	if(!cond(0)){
		cout << 0 << endl;
		return 0;
	}
	if(cond(N-1)){
		cout << N << endl;
		return 0;
	}

	int lb=0, ub=N-1;

	while(ub-lb>1){
		int med = (ub+lb)/2;
		if(cond(med)){
			lb = med;
		}
		else{
			ub = med;
		}
	}

	cout << ub << endl;

	return 0;
}
