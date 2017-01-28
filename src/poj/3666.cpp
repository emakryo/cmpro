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
const int Nmax = 2000;
int N;
int A[Nmax];
int dp[Nmax+1][Nmax+1];

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++) scanf("%d", &A[i]);
	vector<int> asn;
	for(int i=0; i<N; i++) asn.push_back(A[i]);
	sort(asn.begin(), asn.end());

	int ans = 1e9;
	for(int iii=0; iii<2; iii++){

		for(int i=1; i<=N; i++){
			int min_j = 1e9;
			for(int j=0; j<N; j++){
				min_j = min(dp[i-1][j], min_j);
				dp[i][j] = abs(A[i-1]-asn[j])+min_j;
			}
		}
		ans = min(ans, *min_element(dp[N], dp[N]+N));

		reverse(A, A+N);
	}

	printf("%d\n", ans);

	return 0;
}
