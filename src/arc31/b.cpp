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
string A[10];
int dx[] = {0, 1};
int dy[] = {1, 0};

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
			par[rj] = ri;
		}
	}
	bool same(int i, int j){
		return root(i) == root(j);
	}
};

int main(){
	for(int i=0; i<10; i++){
		cin >> A[i];
	}

	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			if(A[i][j] == 'o') continue;
			A[i][j] = 'o';
			UnionFind uf(100);
			for(int x=0; x<10; x++){
				for(int y=0; y<10; y++){
					if(A[x][y] == 'x') continue;
					for(int k=0; k<2; k++){
						if(x+dx[k] < 0 || 10 <= x+dx[k]) continue;
						if(y+dy[k] < 0 || 10 <= y+dy[k]) continue;
						if(A[x+dx[k]][y+dy[k]] == 'x') continue;
						uf.unite(x+dx[k]+10*(y+dy[k]), x+10*y);
					}
				}
			}

			bool ok = true;
			int root = -1;
			for(int x=0; x<10; x++){
				for(int y=0; y<10; y++){
					if(A[x][y] == 'x') continue;
					if(root == -1){
						root = uf.root(x+10*y);
					}
					if(root != uf.root(x+10*y)){
						ok = false;
					}
				}
			}
			
			if(ok){
				cout << "YES" << endl;
				return 0;
			}

			A[i][j] = 'x';
		}
	}

	cout << "NO" << endl;
	return 0;
}
