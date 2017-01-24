#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 1e5;
int N;
ll A[Nmax], X;

int main(){
	cin >> N >> X;
	for(int i=0; i<N; i++) cin >> A[i];

	ll ans = 0;
	for(int i=0; i<N-1; i++){
		if(A[i]+A[i+1]<=X) continue;
		ll t = min(A[i+1], A[i+1]+A[i]-X);
		ans += t;
		A[i+1] -= t;
		//cout << t << endl;
		if(A[i]+A[i+1] > X){
			t = A[i]+A[i+1]-X;
			ans += t;
			A[i] -= t;
			//cout << " " << t << endl;
		}
	}

	cout << ans << endl;

	return 0;
}
