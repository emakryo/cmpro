#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
int N, X;

bool dfs(vector<int> &perm){
	/*
	if(perm.size() > 0){
		printf("%d", perm[0]);
		for(int i=1; i<perm.size(); i++){
			printf(" %d", perm[i]);
		}
		printf("\n");
	}
	*/

	if(perm.size() == N){
		vector<int> xs(perm);
		for(int i=0; i<N-1; i++){
			for(int j=0; j<N-i-1; j++){
				xs[j] = xs[j]+xs[j+1];
			}
		}
		if(xs[0] == X){
			printf("%d", perm[0]);
			for(int i=1; i<N; i++){
				printf(" %d", perm[i]);
			}
			printf("\n");
			return true;
		}
		return false;
	}

	bool done = false;
	for(int i=1; i<=N; i++){
		if(perm.size() > 0){
			int k=0;
			while(k < perm.size() && perm[k] != i) k++;
			//printf("%d/%lu\n", k, perm.size());
			if(k != perm.size()) continue;
		}
		perm.push_back(i);
		if(dfs(perm)){
			done = true;
			break;
		}
		perm.pop_back();
	}

	return done;
}

int main(){
	scanf("%d%d", &N, &X);

	vector<int> perm;
	dfs(perm);
	return 0;
}
