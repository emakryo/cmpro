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
const int Nmax = 200000;
int N;
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	for(int i=1; i<N; i++) A[i] += A[i-1];

	ll ans = 1e18;
	for(int i=0; i<N-1; i++){
		ans = min(ans, abs(A[i]-(A[N-1]-A[i])));
	}

	cout << ans << endl;

	return 0;
}
