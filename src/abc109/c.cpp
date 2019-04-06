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
ll X, x[Nmax];

ll find_gcd(ll x, ll y){
	while(y > 0){
		ll tmp = x % y;
		x = y;
		y = tmp;
	}
	return x;
}

int main(){
	cin >> N >> X;
	for(int i=0; i<N; i++) cin >> x[i];

	vector<ll> dist(N);
	for(int i=0; i<N; i++) dist[i] = abs(x[i]-X);

	if(N==1){
		cout << dist[0] << endl;
		return 0;
	}

	ll gcd = find_gcd(dist[0], dist[1]);
	for(int i=2; i<N; i++) gcd = find_gcd(gcd, dist[i]);

	cout << gcd << endl;

	return 0;
}
