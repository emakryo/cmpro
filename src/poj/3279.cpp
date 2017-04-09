//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 15;
int M, N;
int T[Nmax][Nmax];
int dx[] = {0, 1, 0, -1, 0};
int dy[] = {0, 0, 1, 0, -1};

int main(){
	scanf("%d%d", &M, &N);
	for(int i=0; i<M; i++){
		for(int j=0; j<N; j++){
			scanf("%d", &T[i][j]);
		}
	}

	vector<vector<int> > ans(M, vector<int>(N));;
	vector<vector<int> > tile(M, vector<int>(N));
	vector<vector<int> > flip(M, vector<int>(M));
	int ans_min = 1e8;
	for(int k=0; k<(1<<N); k++){
		for(int i=0; i<M; i++){
			for(int j=0; j<N; j++){
				tile[i][j] = T[i][j];
				flip[i][j] = 0;
			}
		}

		for(int j=0; j<N; j++){
			if(((k>>(N-j-1))&1)==0) continue;
			flip[0][j] = 1;
			for(int l=0; l<5; l++){
				if(0<=dx[l] && dx[l]<M && 0<=j+dy[l] && j+dy[l]<N){
					tile[dx[l]][j+dy[l]] = 1-tile[dx[l]][j+dy[l]];
				}
			}
		}

		for(int i=1; i<M; i++){
			for(int j=0; j<N; j++){
				if(tile[i-1][j] == 0) continue;
				flip[i][j] = 1;
				for(int l=0; l<5; l++){
					if(0<=i+dx[l] && i+dx[l]<M & 0<=j+dy[l] && j+dy[l]<N){
						tile[i+dx[l]][j+dy[l]] = 1-tile[i+dx[l]][j+dy[l]];
					}
				}
			}
		}

		int ok = true;
		for(int j=0; j<N; j++){
			ok = ok && (tile[M-1][j] == 0);
		}
		if(!ok) continue;

		//for(int i=0; i<M; i++){
		//	for(int j=0; j<N; j++){
		//		printf("%d%c", tile[i][j], j!=N-1?' ':'\n');
		//	}
		//}
		//printf("\n");

		int count = 0;
		for(int i=0; i<M; i++){
			for(int j=0; j<N; j++){
				if(flip[i][j]) count++;
			}
		}
		//printf("%d %d\n", k, count);
		//for(int i=0; i<M; i++){
		//	for(int j=0; j<N; j++){
		//		printf("%d%c", flip[i][j], j!=N-1?' ':'\n');
		//	}
		//}
		//printf("\n");

		if(count < ans_min){
			for(int i=0; i<M; i++){
				for(int j=0; j<N; j++){
					ans[i][j] = flip[i][j];
				}
			}
			ans_min = count;
			//printf("%d\n", k);
		}
	}

	if(ans_min == 1e8){
		printf("IMPOSSIBLE\n");
		return 0;
	}

	for(int i=0; i<M; i++){
		for(int j=0; j<N; j++){
			printf("%d%c", ans[i][j], j!=N-1?' ':'\n');
		}
	}
	return 0;
}
