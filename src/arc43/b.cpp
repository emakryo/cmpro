#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Nmax = 1e5;
const int P = 1e9+7;
int N, D[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> D[i];
	sort(D, D+N);

	vector<vector<ll>> cnt(4, vector<ll>(N+1));
	for(int i=0; i<N; i++){
		cnt[0][i] = N-i;
		//cout << 0 << " "<< cnt[0][i] << endl;
	}
	for(int k=0; k<3; k++){
		for(int i=0; i<N; i++){
			cnt[k+1][i] = cnt[k][lower_bound(D, D+N, 2*D[i])-D];
		}
		for(int i=N-2; i>=0; i--){
			cnt[k+1][i] += cnt[k+1][i+1];
			cnt[k+1][i] %= P;
		}
		//for(int i=0; i<N; i++) cout << k+1 << " " <<cnt[k+1][i] << endl;
	}
	cout << cnt[3][0] << endl;

	return 0;
}
