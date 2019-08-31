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
ll L, R;

int main(){
	cin >> L >> R;

	ll ans = 1e5;
	for(ll i=L; i<=min(L+2020, R); i++){
		for(ll j=i+1; j<=min((ll)i+2020, R); j++){
			ans = min(ans, (i*j)%2019);
		}
	}

	cout << ans << endl;

	return 0;
}
