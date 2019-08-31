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
int N;
const int Nmax = 2e5;
int P[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> P[i];

	vector<int> p_inv(N);
	for(int i=0; i<N; i++) p_inv[P[i]-1] = i+1;

	vector<ll> a(N), b(N);
	a[0] = 1;
	b[0] = 9e8-1+p_inv[0];

	for(int i=1; i<N; i++){
		if(p_inv[i]>p_inv[i-1]){
			b[i] = b[i-1]-1;
			a[i] = 9e8+p_inv[i]-b[i];
		} else {
			a[i] = a[i-1]+1;
			b[i] = 9e8+p_inv[i]-a[i];
		}
	}

	for(int i=0; i<N; i++) cout << a[i] << (i==N-1?'\n':' ');
	for(int i=0; i<N; i++) cout << b[i] << (i==N-1?'\n':' ');

	return 0;
}
