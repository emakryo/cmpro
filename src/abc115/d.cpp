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

int main(){
	int N;
	ll X;
	cin >> N >> X;

	vector<ll> total(N+1), p(N+1);
	total[0] = 1;
	p[0] = 1;
	for(int i=1; i<=N; i++){
		total[i] = 2*total[i-1]+3;
		p[i] = 2*p[i-1]+1;
		//cout << total[i] << ' ' << p[i] << endl;
	}

	ll ans = 0;
	for(int i=N-1; i>=0; i--){
		if(X >= total[i]+2){
			ans += p[i]+1;
			X -= total[i]+2;
		} else {
			X -= 1;
		}
	}
	if(X>0) ans++;

	cout << ans << endl;

	return 0;
}
