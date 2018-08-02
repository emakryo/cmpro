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
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];
	sort(A, A+N);

	int n = N-1;
	while(n > 0 && A[n]!=A[n-1]) n--;
	if(n<=0){
		cout << 0 << endl;
		return 0;
	}
	ll ans = A[n];
	n -= 2;
	while(n > 0 && A[n]!=A[n-1]) n--;
	if(n<=0){
		cout << 0 << endl;
		return 0;
	}
	ans *= A[n];
	cout << ans << endl;

	return 0;
}
