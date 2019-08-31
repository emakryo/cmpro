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
const int Mmax = 2e5;
int N, M, A[Mmax];
ll D;

void mul(vector<int> &a, vector<int> &b, vector<int> &c){
	for(int i=0; i<a.size(); i++){
		c[i] = b[a[i]];
	}
}

int main(){
	cin >> N >> M >> D;
	for(int i=0; i<M; i++) cin >> A[i];

	vector<int> perm(N);
	for(int i=0; i<N; i++) perm[i] = i;

	for(int i=M-1; i>=0; i--) swap(perm[A[i]-1], perm[A[i]]);

	vector<int> ans(N);
	for(int i=0; i<N; i++) ans[i] = i;
	for(int k=32; k>=0; k--){
		if((D>>k)==0) continue;
		if(((D>>k)&1)==1){
			vector<int> t1(N), t2(N);
			mul(ans, ans, t1);
			mul(t1, perm, t2);
			ans = t2;
		} else {
			vector<int> t1(N);
			mul(ans, ans, t1);
			ans = t1;
		}
	}

	for(int i=0; i<N; i++) cout << ans[i]+1 << endl;

	return 0;
}
