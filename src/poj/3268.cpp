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
const int Nmax = 1000;
const int Mmax = 1000000;
int N,M,X;
int A[Mmax], B[Mmax], T[Mmax];

int main(){
	scanf("%d%d%d", &N, &M, &X);
	X--;

	for(int i=0; i<M; i++){
		scanf("%d%d%d", &A[i], &B[i], &T[i]);
		A[i]--;
		B[i]--;
	}

	vector<int> dist_forward(N, 1e8);
	vector<int> dist_back(N, 1e8);
	dist_forward[X] = 0;

	bool update = true;
	while(update){
		update = false;
		for(int i=0; i<M; i++){
			if(dist_forward[B[i]] > dist_forward[A[i]] + T[i]){
				dist_forward[B[i]] = dist_forward[A[i]] + T[i];
				update = true;
			}
		}
	}

	dist_back[X] = 0;
	update = true;
	while(update){
		update = false;
		for(int i=0; i<M; i++){
			if(dist_back[A[i]] > dist_back[B[i]] + T[i]){
				dist_back[A[i]] = dist_back[B[i]] + T[i];
				update = true;
			}
		}
	}

	int ans = 0;
	for(int i=0; i<N; i++){
		ans = max(ans, dist_forward[i]+dist_back[i]);
	}
	printf("%d\n", ans);

	return 0;
}
