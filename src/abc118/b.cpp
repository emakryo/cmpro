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
const int Nmax = 30;
int N,M;
int K[Nmax], A[Nmax][Nmax];
int c[Nmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<N; i++){
		cin >> K[i];
		for(int j=0; j<K[i]; j++){
			cin >> A[i][j]; A[i][j]--;
		}
	}

	for(int i=0; i<N; i++){
		for(int j=0; j<K[i]; j++){
			c[A[i][j]]++;
		}
	}

	int ans = 0;
	for(int i=0; i<M; i++){
		if(c[i] == N) ans++;
	}

	cout << ans << endl;

	return 0;
}
