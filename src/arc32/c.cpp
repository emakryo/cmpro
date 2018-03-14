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
const int Nmax = 100000;
const int Xmax = 1000010;
int N, A[Nmax], B[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i] >> B[i];

	vector<vector<int> > Aidx(Xmax);
	int Bmax=0;
	for(int i=0; i<N; i++){
		Aidx[A[i]].push_back(i);
		Bmax = max(Bmax, B[i]);
	}

	vector<pair<int, int> > dp(Xmax);
	for(int i=Xmax-1; i>=0; i--){
		dp[i] = dp[i+1];
		for(int j=0; j<Aidx[i].size(); j++){
			int k = Aidx[i][j];
			if(dp[i].first < dp[B[k]].first+1){
				dp[i] = make_pair(dp[B[k]].first + 1, k);
			}
			else if(dp[i].first == dp[B[k]].first+1 && dp[i].second > k){
				dp[i].second = k;
			}
		}
	}

	//for(int i=0; i<=Bmax; i++) cout << dp[i].first << " " << dp[i].second << endl;

	vector<int> ans;
	int k=0;
	for(int i=0; i<dp[0].first; i++){
		ans.push_back(dp[k].second+1);
		k = B[dp[k].second];
	}

	cout << ans.size() << endl;
	for(int i=0; i<ans.size(); i++){
		cout << ans[i] << (i==ans.size()-1 ? '\n' : ' ');
	}

	return 0;
}
