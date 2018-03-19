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
const int Nmax = 100000;
const ll P = 1e9+7;
int N, T[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> T[i];

	sort(T, T+N);

	ll ans = 0;
	ll acc = 0;
	for(int i=0; i<N; i++){
		acc += T[i];
		ans += acc;
	}

	ll cnt = 1;
	int i=0;
	while(i < N) {
		int d = 1;
		while(T[i+d] == T[i]) d++;
		for(int k=1; k<=d; k++){
			cnt = (cnt * k) % P;
		}
		i += d;
	}

	cout << ans << endl;
	cout << cnt << endl;

	return 0;
}
