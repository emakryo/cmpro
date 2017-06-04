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
ll K;
ll A[Nmax];

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++){
		cin >> A[i];
	}

	vector<ll> b(N+1), d(N+1);
	b[0] = 0;
	for(int i=0; i<N; i++){
		b[i+1] = b[i]+A[i]-K;
	}
	d = b;
	sort(d.begin(), d.end());

	vector<int> c(N+1);
	for(int i=0; i<=N; i++){
		c[i] = lower_bound(d.begin(), d.end(), b[i]) - d.begin();
	}

	vector<int> bit(N+2);
	ll ans = 0;
	for(int i=0; i<=N; i++){
		for(int k=c[i]+1; k>0; k-=k&-k){
			ans += bit[k];
		}
		for(int k=c[i]+1; k<=N+1; k+=k&-k){
			bit[k] += 1;
		}
	}

	cout << ans << endl;

	return 0;
}
