#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int Nmax = 2000;
const int Mmax = 10000;
const long INF = 1e18;
int N,M;
int A[Mmax],B[Mmax];
long L[Mmax];
int par[Nmax], rnk[Nmax];

int root(int n){
	if(par[n] == n) return n;
	return par[n] = root(par[n]);
}

void unite(int n, int m){
	int r=root(n);
	int s=root(m);
	if(r==s) return;
	if(rnk[r] == rnk[s]){
		par[r] = s;
		rnk[r]++;
	}
	else if(rnk[r] > rnk[s]){
		par[s] = r;
	}
	else{
		par[r] = s;
	}
}

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> A[i] >> B[i] >> L[i];
		A[i]--; B[i]--;
	}

	vector<pair<long, int> > cost(M);
	for(int i=0; i<M; i++){
		cost[i]=make_pair(L[i],i);
	}

	for(int i=0; i<N; i++) {
		par[i]=i;
	}

	sort(cost.begin(), cost.end());

	long ans;
	for(int i=0; i<M; i++){
		int k = cost[i].second;
		if(root(A[k]) != root(B[k])){
			unite(A[k],B[k]);
			ans = cost[i].first;
		}
	}

	cout << ans << endl;
	return 0;
}
