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
int N;
ll A[Nmax+1], B[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N+1; i++) cin >> A[i];
	for(int i=0; i<N; i++) cin >> B[i];

	ll ans = 0;
	ll rem = 0;
	for(int i=0; i<N; i++){
		ans += min(A[i], rem+B[i]);
		rem = max(0ll, B[i]-max(0ll, A[i]-rem));
		//cout << ans << " " << rem << endl; 
	}
	ans += min(rem, A[N]);

	cout << ans << endl;


	return 0;
}
