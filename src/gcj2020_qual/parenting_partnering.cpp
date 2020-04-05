#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
	int N;
	cin >> N;
	vector<int> S(N), E(N);
	for(int i=0; i<N; i++) cin >> S[i] >> E[i];

	vector<pair<int, int>> xs(2*N);
	for(int i=0; i<N; i++){
		xs[2*i] = {S[i], i+N};
		xs[2*i+1] = {E[i], i};
	}

	sort(xs.begin(), xs.end());

	string ans(N, 'x');
	int a[2] = {-1, -1};
	for(int i=0; i<2*N; i++){
		int k = xs[i].second;
		if(k>=N){
			k -= N;
			if(a[0]<0){
				a[0]=k;
				ans[k] = 'C';
			} else if(a[1]<0){
				a[1]=k;
				ans[k] = 'J';
			} else {
				printf("IMPOSSIBLE\n");
				return;
			}
		} else {
			if(a[0]==k) a[0]=-1;
			else if(a[1]==k) a[1]=-1;
		}
	}
	printf("%s\n", ans.c_str());
}

int main(){
	int T;
	cin >> T;
	for(int t=1; t<=T; t++){
		printf("Case #%i: ", t);
		solve();
	}

	return 0;
}
