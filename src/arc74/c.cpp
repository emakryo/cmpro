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

ll diff(ll x, ll y, ll z){
	if(x <= y && y <= z) return z-x;
	if(x <= z && z <= y) return y-x;
	if(y <= x && x <= z) return z-y;
	if(y <= z && z <= x) return x-y;
	if(z <= x && x <= y) return y-z;
	return x-z;
}


int main(){
	ll H, W;
	cin >> H >> W;

	if(H%3==0 || W%3==0){
		cout << 0 << endl;
		return 0;
	}

	ll ans = 1e10;
	ans = min(ans, diff((H/3)*W, (H-H/3)*(W/2), (H-H/3)*(W-W/2)));
	ans = min(ans, diff((H/3+1)*W, (H-H/3-1)*(W/2), (H-H/3-1)*(W-W/2)));
	ans = min(ans, diff((W/3)*H, (W-W/3)*(H/2), (W-W/3)*(H-H/2)));
	ans = min(ans, diff((W/3+1)*H, (W-W/3-1)*(H/2), (W-W/3-1)*(H-H/2)));
	ans = min(ans, diff((W/3)*H, (W/3+1)*H, (W-2*W/3-1)*H));
	ans = min(ans, diff((H/3)*W, (H/3+1)*W, (H-2*H/3-1)*W));

	cout << ans << endl;

	return 0;
}
