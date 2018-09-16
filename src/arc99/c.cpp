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
const int Nmax = 1e5;
int N, K, A[Nmax];

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> A[i];

	cout << (N-1) / (K-1) + ((N-1)%(K-1)==0?0:1) << endl;

	return 0;
}
