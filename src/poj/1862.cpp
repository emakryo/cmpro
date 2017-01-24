#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<list>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
int N, W[1000];

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++) scanf("%d", &W[i]);

	sort(W, W+N);
	double ans = W[N-1];
	for(int i=N-2; i>=0; i--){
		ans = 2*sqrt(ans*W[i]);
	}
	printf("%.3lf\n", ans);

	return 0;
}
