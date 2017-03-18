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
const int NMmax = 1000;
int N,M;
ll X0,A,P;

int main(){
	cin >> N >> M;
	cin >> X0 >> A >> P;

	vector<ll> score(N*M);
	vector<pair<ll, int> > vec(N*M);
	score[0] = X0;
	vec[0] = make_pair(X0, 0);
	for(int i=1; i<N*M; i++){
		score[i] = (score[i-1]+A)%P;
		vec[i] = make_pair(score[i], i);
	}

	sort(vec.begin(), vec.end());
	ll ans = 0;
	for(int i=0; i<N*M; i++){
		//cout << vec[i].first << " " << vec[i].second << endl;
		ans += abs(i/M-vec[i].second/M);
	}
	for(int i=0; i<N; i++){
		vector<int> vec2(M);
		for(int j=0; j<M; j++){
			vec2[j] = vec[i*M+j].second%M;
		}
		sort(vec2.begin(), vec2.end());

		for(int j=0; j<M; j++){
			//cout << j << " " << vec2[j] << endl;
			ans += abs(j-vec2[j]);
		}
	}

	cout << ans << endl;

	return 0;
}
