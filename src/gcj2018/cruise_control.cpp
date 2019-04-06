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

double solve(){
	ll D;
	int N;
	cin >> D >> N;
	vector<ll> K(N), S(N);
	for(int i=0; i<N; i++){
		cin >> K[i] >> S[i];
	}

	double ans = 1e20;
	for(int i=0; i<N; i++){
		ans = min(ans, (double)D*S[i]/(D-K[i]));
	}
	return ans;
}


int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		double ans = solve();
		cout << "Case #" << i+1 << ": ";
		cout << setprecision(10) << ans << endl;
	}

	return 0;
}
