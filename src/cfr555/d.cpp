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
ll N;
int K;

int main(){
	cin >> N >> K;
	ll last = -1;
	vector<int> ans;
	for(int i=0; i<K; i++){
		ll x = (K-i)*(K-i+1)/2;
		if(N<x) {
			cout << "NO" << endl;
			return 0;
		}
		ll y;
		if(last > 0) y = min(2*last, 1+(N-x)/(K-i));
		else y = 1+(N-x)/(K-i);
		if(last > 0 && y <= last){
			cout << "NO" << endl;
			return 0;
		}
		last = y;
		N -= y;
		//cout << x << " " << y << endl;
		ans.push_back(y);
	}
	if(N==0){
		cout << "YES" << endl;
		for(int i=0; i<ans.size(); i++) cout << ans[i] << (i<ans.size()?' ':'\n');
	} else {
		cout << "NO" << endl;
		//for(int i=0; i<ans.size(); i++) cout << ans[i] << (i<ans.size()?' ':'\n');
	}

	return 0;
}
