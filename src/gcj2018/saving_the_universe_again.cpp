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

ll damage(string P){
	ll ans = 0;
	ll x = 1;
	for(int i=0; i<P.length(); i++){
		if(P[i]=='S') ans += x;
		else x <<= 1;
	}
	return ans;
}


ll solve(ll D, string P){
	int n = P.length();
	int n_s = 0;
	for(int i=0; i<n; i++){
		if(P[i] == 'S') n_s++;
	}
	if(n_s > D) return -1;

	ll ans = 0;
	while(damage(P) > D){
		//cout << damage(P) << endl;
		int k = n-1;
		while(k>0 && !(P[k]=='S' && P[k-1]=='C')) k--;
		P[k]='C';
		P[k-1]='S';
		ans++;
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		ll D;
		string P;
		cin >> D >> P;
		ll ans = solve(D, P);

		cout << "Case #" << (i+1) << ": ";
		if(ans >= 0) cout << ans << endl;
		else cout << "IMPOSSIBLE" << endl;;
	}

	return 0;
}
