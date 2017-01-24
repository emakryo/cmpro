#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 100000;
int N, D[Nmax], T[Nmax];

bool cmp(pair<int, int> x, pair<int, int> y){
	return x.first*y.second < y.first*x.second;
}

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++) scanf("%d%d", &T[i], &D[i]);
	vector<pair<int, int> > vec(N);
	for(int i=0; i<N; i++) vec[i] = make_pair(T[i],D[i]);

	sort(vec.begin(), vec.end(), cmp);

	ll ans = 0;
	ll t = 0;
	for(int i=0; i<N; i++){
		ans += t*vec[i].second;
		t += 2*vec[i].first;
	}

	printf("%lld\n", ans);
	return 0;
}
