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
const ll P = 1e9+7;

int main(){
	int N;
	cin >> N;

	vector<string> u;
	u.push_back("");
	for(int i=0; i<3; i++){
		vector<string> v;
		for(string s: u){
			for(char a: "ACGT"){
				if(a) v.push_back(s+a);
			}
		}
		u = vector<string>(v);
	}

	vector<vector<ll> > dp(2, vector<ll>(u.size()));
	for(int j=0; j<u.size(); j++){
		if(u[j]=="AGC"||u[j]=="GAC"||u[j]=="ACG") continue;
		dp[0][j] = 1;
	}
	for(int i=0; i<N-3; i++){
		dp[(i+1)%2] = vector<ll>(u.size());
		for(int j=0; j<u.size(); j++){
			for(char c: "ACGT"){
				if(!c) continue;
				string x = u[j]+c;
				string y = x.substr(1);
				if(y=="AGC"||y=="GAC"||y=="ACG"||
					(x[0]=='A'&&x[2]=='G'&&x[3]=='C')||
					(x[0]=='A'&&x[1]=='G'&&x[3]=='C')){
					continue;
				}
				int n = find(u.begin(), u.end(), y)-u.begin();
				dp[(i+1)%2][n] += dp[i%2][j];
				dp[(i+1)%2][n] %= P;
			}
		}
	}

	ll ans = 0;
	for(int j=0; j<u.size(); j++){
		//cout << u[j] << endl;
		ans += dp[(N-3)%2][j];
	}
	cout << ans%P << endl;

	return 0;
}
