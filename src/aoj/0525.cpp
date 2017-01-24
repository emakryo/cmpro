#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
int R, C;
int A[10][10000];

int dfs(int state, int n){
	if(n == R){
		int ans = 0;
		for(int i=0; i<C; i++){
			int t=0;
			for(int j=0; j<R; j++){
				t += (state>>j)&1 ? A[j][i] : 1-A[j][i];
			}
			ans += max(t, R-t);
		}
		return ans;
	}

	return max(dfs(state, n+1), dfs(state|(1<<n), n+1));
}


int main(){
	while(true){
		scanf("%d%d", &R, &C);
		if(R==0 && C==0) break;
		for(int i=0; i<R; i++){
			for(int j=0; j<C; j++){
				scanf("%d", &A[i][j]);
			}
		}

		int ans = dfs(0, 0);
		printf("%d\n", ans);
	}

	return 0;
}
