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
int N, K;
ll H[Nmax];

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> H[i];

	sort(H, H+N);

	ll ans = H[K-1]-H[0];
	for(int i=0; i<=N-K; i++) ans = min(ans, H[i+K-1]-H[i]);
	cout << ans << endl;

	return 0;
}
