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
const int Nmax=1e5;
int N, M;
int X[Nmax];
int d[Nmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++) cin >> X[i];
	sort(X, X+M);

	for(int i=0; i<M-1; i++) d[i] = X[i+1]-X[i];

	sort(d, d+M-1);

	ll ans = 0;
	for(int i=0; i<M-N; i++) ans += d[i];

	cout << ans << endl;

	return 0;
}
