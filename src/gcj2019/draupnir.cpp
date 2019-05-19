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

int solve(){
	ll buf[2];
	cout << 56 << endl;
	cout << 168 << endl;
	cin >> buf[0] >> buf[1];
	if(buf[0]<0||buf[1]<0) return -1;

	ll ans[6];
	ans[0] = (buf[0] >> 56)&((1<<8)-1);
	ans[1] = (buf[0] >> 28)&((1<<8)-1);
	ans[2] = (buf[1] >> 56)&((1<<8)-1);
	ans[3] = (buf[1] >> 42)&((1<<8)-1);
	buf[0] -= (ans[0]<<56) + (ans[1]<<28) + (ans[2]<<18) + (ans[3]<<14);
	buf[1] -= (ans[2]<<56) + (ans[3]<<42);
	buf[0] >>= 9;
	buf[1] >>= 28;
	ans[4] = (buf[1]-buf[0])/28;
	ans[5] = (8*buf[0]-buf[1])/7;
	cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << " " << ans[4] << " " <<ans[5] << endl;
	int r;
	cin >> r;
	return r;
}

int main(){
	int t, w;
	cin >> t >> w;
	for(int i=0; i<t; i++){
		if(solve()<0) break;
	}

	return 0;
}
