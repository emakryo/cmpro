#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
const int Nmax = 1e5;
ll A[Nmax], B[Nmax], C[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];
	for(int i=0; i<N; i++) cin >> B[i];
	for(int i=0; i<N; i++) cin >> C[i];

	sort(A, A+N);
	sort(B, B+N);
	sort(C, C+N);

	/*
	for(int i=0; i<N; i++) cout << A[i] << (i==N-1?'\n':' ');
	for(int i=0; i<N; i++) cout << B[i] << (i==N-1?'\n':' ');
	for(int i=0; i<N; i++) cout << C[i] << (i==N-1?'\n':' ');
	*/

	vector<int> bn(N);
	for(int i=0; i<N; i++){
		bn[i] = C+N-lower_bound(C, C+N, B[i]+1);
	}
	//for(int i=0; i<N; i++) cout << bn[i] << (i==N-1?'\n':' ');
	vector<ll> bcum(N);
	bcum[N-1] = bn[N-1];
	for(int i=N-2; i>=0; i--) bcum[i]=bcum[i+1]+bn[i];
	//for(int i=0; i<N; i++) cout << bcum[i] << (i==N-1?'\n':' ');

	ll ans = 0;
	for(int i=0; i<N; i++){
		int k = lower_bound(B, B+N, A[i]+1)-B;
		//cout << k << endl;
		if(k<N) ans += bcum[k];
	}

	cout << ans << endl;

	return 0;
}
