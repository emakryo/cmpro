
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
const int Nmax = 100000;
int A[Nmax], R, L, N;

int main(){
	cin >> N >> L >> R;
	for(int i=0; i<N; i++) cin >> A[i];

	for(int i=0; i<N; i++){
		cout << max(L, min(R, A[i])) << (i!=N-1? ' ' : '\n');
	}

	return 0;
}
