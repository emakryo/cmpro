#include<vector>
#include<iostream>
using namespace std;

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
