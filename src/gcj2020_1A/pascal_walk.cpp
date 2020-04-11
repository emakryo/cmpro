#include<bits/stdc++.h>
#include<cassert>
using namespace std;
typedef long long ll;

void check(int n, vector<pair<int, int>> &ans){
	vector<vector<ll>> pascal(70, vector<ll>(70));
	for(int i=1; i<70; i++) for(int j=1; j<=i; j++) {
		if(j==i||j==1) pascal[i][j] = 1;
		else pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
	}
	assert(ans[0].first == 1 && ans[0].second == 1);
	int sum = 1;
	for(int i=1; i<ans.size(); i++){
		//cout << ans[i].first << " " << ans[i].second << endl;
		sum += pascal[ans[i].first][ans[i].second];
	}

	assert(sum == n);
	assert(ans.size() <= 500);
}

void solve(){
	int N;
	cin >> N;

	int m = min(N, 31);
	int n = N-m;

	int z = 0;
	vector<pair<int, int>> ans;
	for(int k=0; n>>k; k++){
		bool left = ans.empty()?true:ans.rbegin()->second==1;
		if(n>>k & 1) {
			for(int i=0; i<k+1; i++){
				ans.push_back({k+1, left?i+1:k-i+1});
			}
		} else {
			ans.push_back({k+1, left?1:k+1});
			z++;
		}
	}

	for(int i=0; i<m-z; i++){
		bool left = ans.empty()?true:ans.rbegin()->second==1;
		int k = ans.empty()?0:ans.rbegin()->first;
		ans.push_back({k+1, left?1:k+1});
	}

	cout << endl;
	check(N, ans);

	for(auto p: ans){
		cout << p.first << " " << p.second << endl;
	}
}


int main(){
	int T;
	cin >> T;
	for(int t=1; t<=T; t++){
		cout << "Case #" << t << ": ";
		solve();
	}

	return 0;
}
