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
int N, K;
ll A[Nmax];

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> A[i];

	sort(A, A+N);

	ll ans=0;
	for(int i=0; i<K; i++) ans += A[i]+i;

	cout << ans << endl;

	return 0;
}
