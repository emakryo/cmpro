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
ll N, M;

int main(){
	cin >> N >> M;
	ll ans;
	if(N==1&&M==1){
		ans = 1;
	} else if(N==1){
		ans = M-2;
	} else if(M==1){
		ans = N-2;
	} else {
		ans = (N-2)*(M-2);
	}
	cout << ans << endl;

	return 0;
}
