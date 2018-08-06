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
const int Qmax = 100;
int Q;
ll A[Qmax], B[Qmax];

int main(){
	cin >> Q;
	//for(int i=0; i<Q; i++) cin >> A[i] >> B[i];

	for(int i=0; i<Q; i++){
		cin >> A[i] >> B[i];
		ll lb=0, ub=1e9;
		while(ub-lb>1){
			ll med = (ub+lb)/2;
			if(med*med <= A[i]*B[i]-1) lb = med;
			else ub = med;
		}
		ll x = lb;
		if(x == 0){
			cout << 0 << endl;
			continue;
		}
		ll y = (A[i]*B[i]-1)/x;
		ll ans = (x==y)?(2*x-1):2*x;
		if(A[i]<=x || B[i]<=x) ans -= 1;
		cout << ans << endl;
	}

	return 0;
}
