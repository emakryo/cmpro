#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
	string S;
	cin >> S;
	
	int n = S.size();
	string ans;
	for(int i=0; i<=n; i++){
		int d;
		if(i==0) d = S[0]-'0';
		else if(i==n) d = -(int)(S[n-1]-'0');
		else d = (int)S[i] - (int)S[i-1];

		for(int k=0; k<abs(d); k++){
			ans += d>0?"(":")";
		}
		if(i<n) ans += S[i];
	}
	cout << ans << endl;
}

int main(){
	int T; cin >> T; 
	for(int t=1; t<=T; t++){
		printf("Case #%i: ", t);
		solve();
	}
	return 0;
}
