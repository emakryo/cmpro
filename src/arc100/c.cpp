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

	for(int i=0; i<N; i++) A[i] -= i+1;
	sort(A, A+N);

	ll x = 0;
	for(int i=0; i<N; i++){
		x += A[i]-A[0];
	}

	ll ans = x;
	for(int i=1; i<N; i++){
		x += i*(A[i]-A[i-1]) - (N-i)*(A[i]-A[i-1]);
		if(x < ans) ans = x;
	}

	cout << ans << endl;

	return 0;
}
