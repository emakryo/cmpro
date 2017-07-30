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
const int Nmax = 50;
int N;
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> A[i];
	}

	ll ans = 0;
	while(true){
		ll x = 0;
		for(int i=0; i<N; i++){
			x += A[i]/N;
		}
		ans += x;
		for(int i=0; i<N; i++){
			A[i] += x - (A[i]/N)*(N+1);
		}

		bool f = true;
		for(int i=0; i<N; i++){
			f = f && A[i] < N;
		}

		if(f) break;
	}

	cout << ans << endl;

	return 0;
}
