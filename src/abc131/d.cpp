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

	vector<pair<ll, ll> > v(N);
	for(int i=0; i<N; i++) v[i] = {B[i], A[i]};
	sort(v.begin(), v.end());

	ll t = 0;
	for(int i=0; i<N; i++){
		t += v[i].second;
		if(t > v[i].first){
			cout << "No" << endl;
			return 0;
		}
	}

	cout << "Yes" << endl;

	return 0;
}
