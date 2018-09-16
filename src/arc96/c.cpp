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
ll A, B, C, X, Y;

int main(){
	cin >> A >> B >> C >> X >> Y;

	ll ans = 1e10;;
	for(ll z=0; z<=max(X,Y); z++){
		ans = min(ans, 2*z*C + max(0LL, X-z)*A + max(0LL, Y-z)*B);
	}

	cout << ans << endl;

	return 0;
}
