
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
int N;
string S;

int main(){
	cin >> N >> S;

	vector<int> nE(N);
	for(int i=0; i<N; i++){
		nE[i] = i==0?0:nE[i-1];
		nE[i] += S[i]=='E'?1:0;
	}
	int ans = 1e8;
	for(int i=0; i<N; i++){
		int left = i>0?i-nE[i-1]:0;
		int right = nE[N-1]-nE[i];
		ans = min(ans, left+right);
	}

	cout << ans << endl;

	return 0;
}
