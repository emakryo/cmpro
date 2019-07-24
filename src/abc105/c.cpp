#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N;

int main(){
	cin >> N;

	ll even=0, odd=0;
	for(int k=0; k<=40; k++){
		if(k%2) odd += 1ll<<k;
		else even += 1ll<<k;
	}

	string ans;
	for(int k=40; k>0; k--){
		//if(k%2) cout << -(((1ll<<(k-1))-1)&odd) << " " << N << " " << -(((1ll<<(k+1))-1)&odd) << endl;
		//else cout << (((1ll<<(k-1))-1)&even) << " " << N << " " << (((1ll<<(k+1))-1)&even) << endl;
		if(k%2 && (((1ll<<(k-1))-1)&odd) < -N && -N <= (((1ll<<(k+1))-1)&odd)){
			ans += '1';
			N += 1ll<<k;
		} else if(!(k%2) && (((1ll<<(k-1))-1)&even) < N && N <= (((1ll<<(k+1))-1)&even)){
			ans += '1';
			N -= 1ll<<k;
		} else{
			ans += '0';
		}
	}

	if(N==1) ans += '1';
	else ans += '0';

	auto nonzero = 0;
	while(nonzero<ans.size() && ans[nonzero]=='0') nonzero++;

	if(nonzero==ans.size()) cout << 0 << endl;
	else cout << ans.substr(nonzero) << endl;

	return 0;
}
