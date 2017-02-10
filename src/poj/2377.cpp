//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;

class UnionFind{
	vector<int> par, rnk;
	public:
	UnionFind(int n){
		par=vector<int>(n);
		rnk=vector<int>(n,0);
		for(int i=0; i<n; i++) par[i]=i;
	}
	int root(int i){
		if(par[i]==i) return i;
		return par[i]=root(par[i]);
	}
	void unite(int i, int j){
		int ri = root(i);
		int rj = root(j);
		if(ri==rj) return;

		if(rnk[ri]==rnk[rj]){
			par[ri] = rj;
			rnk[rj]++;
		}
		else if(rnk[ri] < rnk[rj]){
			par[ri] = rj;
		}
		else{
			rnk[rj] = ri;
		}
	}
	bool same(int i, int j){
		return root(i) == root(j);
	}
};

int main(){
	int N, M;
	scanf("%d%d", &N, &M);
	vector<int> A(M),B(M);
	vector<pair<int, int> > edge(M);
	for(int i=0; i<M; i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		A[i] = a-1;
		B[i] = b-1;
		edge[i] = make_pair(-c, i);
	}

	sort(edge.begin(), edge.end());

	UnionFind uf(N);
	int ans = 0;
	int cnt = 0;
	for(int i=0; i<M; i++){
		int k = edge[i].second;
		if(!uf.same(A[k], B[k])){
			uf.unite(A[k], B[k]);
			ans += edge[i].first;
			cnt++;
		}
	}

	printf("%d\n", cnt==N-1 ? -ans : -1);

	return 0;
}
