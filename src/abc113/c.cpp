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
const int Mmax = 1e5;
int N, M, P[Mmax];
ll Y[Mmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++) cin >> P[i] >> Y[i];
	
	vector<int> pcount(N+1);
	vector<pair<ll, int>> yidx(M);
	for(int i=0; i<M; i++) yidx[i] = {Y[i], i};
	sort(yidx.begin(), yidx.end());

	vector<ll> ans(M);

	for(int i=0; i<M; i++){
		int n = yidx[i].second;
		pcount[P[n]]++;
		ans[n] = P[n]*1000000ll + pcount[P[n]];
	}

	for(int i=0; i<M; i++){
		cout << setw(12) << setfill('0') << ans[i] << endl;
	}

	return 0;
}
