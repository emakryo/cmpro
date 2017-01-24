#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Mmax = 1000;
const int Nmax = 1000000;
int N, M, R;
int S[Mmax], T[Mmax], E[Mmax];
ll dp[Nmax+1];

int main(){
	scanf("%d%d%d", &N,&M,&R);
	for(int i=0; i<M; i++){
		scanf("%d%d%d", &S[i], &T[i], &E[i]);
	}

	vector<pair<int, int> > vec;
	for(int i=0; i<M; i++){
		vec.push_back(make_pair(T[i], i));
	}

	sort(vec.begin(), vec.end());

	int n = 0;
	for(int i=1; i<N+1; i++){
		dp[i] = dp[i-1];
		while(n < M && vec[n].first <= i){
			int k = vec[n].second;
			dp[i] = max(dp[i], dp[max(0, S[k]-R)]+E[k]);
			n++;
		}
		printf("%lld\n", dp[i]);
	}

	printf("%lld\n", dp[N]);
	return 0;
}
