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
const int Mmax = 200000;
int N, M;
int A[Mmax], B[Mmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++){
		cin >> A[i] >> B[i];
		A[i]--;
		B[i]--;
	}

	vector<bool> vec(N);
	for(int i=0; i<M; i++){
		if(A[i] == 0) vec[B[i]] = true;
		if(B[i] == 0) vec[A[i]] = true;
	}
	for(int i=0; i<M; i++){
		if((vec[A[i]] && B[i] == N-1) || (vec[B[i]] && A[i] == N-1)){
			cout << "POSSIBLE" << endl;
			return 0;
		}
	}

	cout << "IMPOSSIBLE" << endl;


	return 0;
}
