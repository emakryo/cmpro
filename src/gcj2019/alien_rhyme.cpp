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

int rec(vector<string> &X, int s, int t, int n){
	int i=s;
	int ret = 0;
	if(t-s==2) return 2;
	if(t-s<2) return 0;
	while(i<t){
		int j=i+1;
		while(j<t && X[i][n]==X[j][n]) j++;
		if(j-i==1){
			i=j;
			continue;
		}
		ret += rec(X, i, j, n+1);
		i=j;
	//cout << i << " " << j << " " << s << " " << t << " " << n << endl;
	}
	if(t-s - ret >= 2) ret += 2;
	//cout << X[s].substr(0, n) << " " << ret << endl;
	return ret;
}

int solve(){
	int N;
	vector<string> X;
	cin >> N;
	for(int i=0; i<N; i++){
		string s;
		cin >> s;
		reverse(s.begin(), s.end());
		X.push_back(s);
	}
	sort(X.begin(), X.end());
	//for(int i=0; i<N; i++) cout << X[i] << endl;
	int s = 0;
	int ans = 0;
	while(s<N){
		int t = s+1;
		while(t<N && X[s][0]==X[t][0]) t++;
		ans += rec(X, s, t, 1);
		s = t;
	}

	return ans;
}

int main(){
	int T, N;
	cin >> T;
	for(int i=0; i<T; i++){
		cout << "Case #" << i+1 << ": " << solve() << endl;
	}

	return 0;
}
