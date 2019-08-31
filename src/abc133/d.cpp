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

	ll sum = 0;
	ll even = 0, odd = 0;
	for(int i=0; i<N; i++){
		sum += A[i];
		if(i%2) odd += A[i];
		else even += A[i];
	}

	ll ans = sum - 2*odd;
	cout << ans << " ";
	for(int i=0; i<N-1; i++){
		ans = 2*A[i]-ans;
		cout << ans << (i==N-1?'\n':' ');
	}

	return 0;
}
