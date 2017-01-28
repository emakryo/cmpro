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
const int Nmax = 400;
int N, A[Nmax], H[Nmax], C[Nmax];
bool dp[40001];

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d%d%d", &H[i], &A[i], &C[i]);
	}

	vector<pair<int, int> > vec;
	for(int i=0; i<N; i++){
		vec.push_back(make_pair(A[i], i));
	}
	sort(vec.begin(), vec.end());

	dp[0] = true;
	for(int i=0; i<N; i++){
		int j = vec[i].second;
		for(int l=0; l<C[j]; l++){
			for(int k=A[j]; k>0; k--){
				if(k-H[j]>=0){
					dp[k] = dp[k] || dp[k-H[j]];
				}
			}
		}
	}

	int ans = A[vec.rbegin()->second];
	while(!dp[ans]) ans--;
	printf("%d\n", ans);


	return 0;
}
