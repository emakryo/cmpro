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
const int Nmax = 100000;
int N;
ll A, B, H[Nmax];

bool condition(ll x){
	ll center = 0;
	for(int i=0; i<N; i++){
		ll remain = max(0LL, H[i]-B*x);
		center += remain/(A-B) + (remain%(A-B)==0 ? 0 : 1);
	}
	return center <= x;
}

int main(){
	cin >> N >> A >> B;
	for(int i=0; i<N; i++){
		cin >> H[i];
	}

	ll lb = 0, ub = 1e9;
	while(ub-lb>1){
		ll mid = (ub+lb)/2;
		if(condition(mid)){
			ub = mid;
		}
		else{
			lb = mid;
		}
	}

	cout << ub << endl;

	return 0;
}
