#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 100000;
int N, M, K;
int L[Nmax], R[Nmax];

int main(){
	cin >> N >> M;
	vector<vector<ll> > A(N, vector<ll>(M));
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			cin >> A[i][j];
		}
	}
	cin >> K;
	for(int i=0; i<K; i++){
		cin >> L[i] >> R[i];
		L[i]--;
	}

	vector<int> limit(N);
	vector<int> start(M,0);
	for(int i=1; i<N; i++){
		for(int j=0; j<M; j++){
			if(A[i][j] < A[i-1][j]){
				start[j] = i;
			}
		}

		int min_start = N;
		for(int j=0; j<M; j++){
			min_start = min(min_start, start[j]);
		}

		limit[min_start] = max(limit[min_start], i);
	}

	for(int i=1; i<N; i++){
		limit[i] = max(limit[i-1], limit[i]);
	}

	/*
	for(int i=0; i<N; i++){
		cout << limit[i] << endl;
	}
	*/

	for(int i=0; i<K; i++){
		if(limit[L[i]]+1 >= R[i]) cout << "Yes" << endl;
		else cout << "No" << endl;
	}

	return 0;
}
