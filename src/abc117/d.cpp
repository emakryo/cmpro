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
const int Nmax=1e5;
int N;
ll K, A[Nmax];

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> A[i];

	ll ans=0, x=0;
	for(int k=60; k>=0; k--){
		ll t = 1L<<k;
		int b=0;
		for(int i=0; i<N; i++){
			if((A[i]&t)) b++;
		}
		if(b < N-b && (t+x) <= K){
			x+=t;
			ans+=(N-b)*t;
		} else {
			ans+=b*t;
		}
	}

	cout << ans << endl;

	return 0;
}
