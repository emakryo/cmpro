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
const int Nmax = 2e5;
int N;
ll A[Nmax], B[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i] >> B[i];

	ll sum = 0;
	bool same = true;
	for(int i=0; i<N; i++){
		sum += A[i];
		same = same && (A[i]==B[i]);
	}
	if(same){
		cout << 0 << endl;
		return 0;
	}

	ll m=1e10;
	for(int i=0; i<N; i++){
		if(A[i]>B[i] && B[i] < m) m = B[i];
	}
	cout << sum-m << endl;

	return 0;
}
