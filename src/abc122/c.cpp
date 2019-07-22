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
const int Qmax = 1e5;
int N, Q;
string S;
int L[Qmax], R[Qmax];

int main(){
	cin >> N >> Q >> S;
	for(int i=0; i<Q; i++) cin >> L[i] >> R[i];

	vector<int> cnt(N+1);
	for(int i=2; i<=N; i++){
		cnt[i] = cnt[i-1];
		if(S[i-2]=='A'&&S[i-1]=='C') cnt[i]++;
		cout << i << " " << cnt[i] << endl;
	}

	for(int i=0; i<Q; i++){
		cout << cnt[R[i]]-cnt[L[i]] << endl;
	}

	return 0;
}
