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
	ll N;
	cin >> N;

	vector<ll> ans;
	for(ll x=max(1LL, N-162); x<=N-1; x++){
		ll f = 0;
		ll d = 1;
		for(int i=0; i<20; i++){
			f += (x/d)%10;
			d *= 10;
		}
		if(x + f == N){
			ans.push_back(x);
		}
	}

	cout << ans.size() << endl;
	for(int i=0; i<ans.size(); i++) cout << ans[i] << endl;

	return 0;
}
