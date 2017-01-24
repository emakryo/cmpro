#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 10000;
int N, S, C[Nmax], Y[Nmax];

int main(){
	scanf("%d%d", &N, &S);
	for(int i=0; i<N; i++){
		scanf("%d%d", &C[i], &Y[i]);
	}

	int lowest = 0;
	ll ans = C[0]*Y[0];
	for(int i=1; i<N; i++){
		if(C[lowest] + S*(i-lowest) < C[i]){
			ans += (C[lowest]+S*(i-lowest))*Y[i];
		}
		else{
			ans += C[i]*Y[i];
			lowest = i;
		}
	}

	printf("%lld\n", ans);

	return 0;
}
