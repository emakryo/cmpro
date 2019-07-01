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
int N, M, A, B;
const int Mmax=200;
int L[Mmax], R[Mmax];

int main(){
	cin >> N >> M >> A >> B;
	vector<int> v(N, B);

	for(int i=0; i<M; i++){
		int l, r;
		cin >> l >> r;
		for(int k=l-1; k<r; k++) v[k] = A;
	}

	int ans = 0;
	for(int i=0; i<N; i++) ans += v[i];
	cout << ans << endl;

	return 0;
}
