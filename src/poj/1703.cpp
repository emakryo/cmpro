//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<sstream>
using namespace std;
typedef long long ll;
const int Nmax = 100000;
const int Mmax = 100000;
int N, M;

class UnionFind{
	vector<int> par, rnk;
	public:
	UnionFind(int n){
		par=vector<int>(n);
		rnk=vector<int>(n,0);
		for(int i=0; i<n; i++) par[i]=i;
	}
	int root(int i, int &d){
		if(par[i]==i) {
			d = 0;
			return i;
		}
		int r = root(par[i], d);
		if(d%2==0){
			par[i] = r;
		}
		d++;
		return r;
	}
	void unite(int i, int j){
		int di,dj;
		int ri = root(i,di);
		int rj = root(j,dj);
		if(ri == rj) return;

		if(di == 0){
			par[ri] = j;
		}
		else if(dj == 0){
			par[rj] = i;
		}
		else if(di%2 == dj%2){
			par[rj] = ri;
		}
		else if(di > dj){
			par[rj] = dj%2==0 ? i : par[i];
		}
		else{
			par[ri] = di%2==0 ? j : par[j];
		}
	}
	int same(int i, int j){
		int di,dj;
		int ri = root(i, di);
		int rj = root(j, dj);
		if(ri != rj) return 0;
		return di%2 == dj%2 ? 1 : -1;
	}
};

int main(){
	int T;
	scanf("%d", &T);
	for(int iii=0; iii<T; iii++){
		scanf("%d%d", &N, &M);
		UnionFind uf(N);
		for(int i=0; i<M; i++){
			char s[5];
			int a,b;
			scanf("%s%d%d", s, &a, &b);
			a--; b--;
			if(s[0] == 'A'){
				int r = uf.same(a, b);
				if(r==0){
					printf("Not sure yet.\n");
				}else if(r > 0){
					printf("In the same gang.\n");
				}else{
					printf("In different gangs.\n");
				}
			}
			else{
				uf.unite(a, b);
			}
		}
	}


	return 0;
}
