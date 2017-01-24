#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int INF = 1e8;
const int Nmax = 100;
int N,A[Nmax],B[Nmax],C[Nmax],M;
int d[10][10];

int solve(){
	cin >> N;
	if(N == 0) return -1;
	for(int i=0; i<N; i++) cin >> A[i] >> B[i] >> C[i];

	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			d[i][j] = INF;
		}
	}
	for(int i=0; i<10; i++){
		d[i][i] = 0;
	}

	M = 0;
	for(int i=0; i<N; i++){
		d[A[i]][B[i]] = C[i];
		d[B[i]][A[i]] = C[i];
		M = max(M, max(A[i],B[i])+1);
	}

	for(int k=0; k<M; k++){
		for(int i=0; i<M; i++){
			for(int j=0; j<M; j++){
				if(d[i][k] + d[k][j] < d[i][j]){
					d[i][j] = d[i][k] + d[k][j];
				}
			}
		}
	}

	/*
	for(int i=0; i<M; i++){
		for(int j=0; j<M; j++){
			cout << d[i][j] << " ";
		}
		cout << endl;
	}
	*/

	int min_i = 0;
	int min_sum = INF;
	for(int i=0; i<M; i++){
		int sum=0;
		for(int j=0; j<M; j++){
			sum += d[i][j];
		}
		if(sum < min_sum){
			min_sum = sum;
			min_i = i;
		}
	}

	cout << min_i << " " << min_sum << endl;
	return 0;
}

int main(){
	while(solve()==0){}
	return 0;
}
