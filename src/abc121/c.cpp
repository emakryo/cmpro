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
int N, M, B[Nmax];
ll A[Nmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<N; i++) cin >> A[i] >> B[i];

	vector<pair<ll, int> > xs(N);
	for(int i=0; i<N; i++) xs[i] = {A[i], B[i]};
	sort(xs.begin(), xs.end());

	ll sum = 0;
	for(int i=0; i<N; i++){
		ll a = xs[i].first;
		int b = xs[i].second;
		if(M>b){
			sum += a*b;
			M -= b;
		} else {
			sum += a*M;
			break;
		}
	}

	cout << sum << endl;

	return 0;
}
