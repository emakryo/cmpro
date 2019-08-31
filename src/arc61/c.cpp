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
int N, A[Nmax], B[Nmax];
ll K;

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> A[i] >> B[i];

	vector<pair<int, int> > v;
	for(int i=0; i<N; i++) v.push_back({A[i], B[i]});
	sort(v.begin(), v.end());

	vector<ll> c(N);
	c[0] = v[0].second;
	for(int i=1; i<N; i++) c[i] = c[i-1]+v[i].second;

	auto k = lower_bound(c.begin(), c.end(), K);
	cout << v[k-c.begin()].first << endl;

	return 0;
}
