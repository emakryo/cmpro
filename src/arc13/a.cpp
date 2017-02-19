//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	int N,M,L,P,Q,R;
	scanf("%d%d%d", &N, &M, &L);
	scanf("%d%d%d", &P, &Q, &R);

	int ans = 0;
	ans = max(ans, (N/P) * (M/Q) * (L/R));
	ans = max(ans, (N/P) * (M/R) * (L/Q));
	ans = max(ans, (N/Q) * (M/P) * (L/R));
	ans = max(ans, (N/Q) * (M/R) * (L/P));
	ans = max(ans, (N/R) * (M/P) * (L/Q));
	ans = max(ans, (N/R) * (M/Q) * (L/P));

	printf("%d\n", ans);

	return 0;
}
