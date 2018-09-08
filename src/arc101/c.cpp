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
const int Nmax = 1e5;
int N, K, X[Nmax];

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> X[i];

	int ans = 1e9;
	for(int i=0; i<N-K+1; i++){
		if(X[i+K-1]<=0) ans=min(ans, -X[i]);
		else if(X[i]>=0) ans=min(ans, X[i+K-1]);
		else ans = min(ans, min(-2*X[i]+X[i+K-1], -X[i]+2*X[i+K-1]));
	}

	cout << ans << endl;

	return 0;
}
