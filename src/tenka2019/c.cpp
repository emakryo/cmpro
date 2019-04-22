
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
	int N;
	string S;
	cin >> N;
	cin >> S;
	vector<int> blackcum(1);
	for(int i=0; i<N; i++){
		if(S[i]=='#') blackcum.push_back(blackcum[i]+1);
		else blackcum.push_back(blackcum[i]);
	}

	int ans = 1e8;
	for(int i=0; i<=N; i++){
		cout << blackcum[i] << " " << N-i-blackcum[N]+blackcum[i] << endl;
		ans = min(ans, blackcum[i]+(N-i-blackcum[N]+blackcum[i]));
	}
	cout << ans << endl;

	return 0;
}
