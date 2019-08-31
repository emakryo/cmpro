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
int N;

int main(){
	cin >> N;

	int s = N%2?N:N+1;
	vector<pair<int, int>> ans, cmp;
	for(int u=1; u<=N/2; u++){
		cmp.push_back({u, s-u});
	}
	if(N%2){
		cmp.push_back({0, N});
	}
	for(int i=0; i<cmp.size(); i++){
		auto next = cmp[(i+1)%cmp.size()];
		if(cmp[i].first>0&&next.first>0){
			ans.push_back({cmp[i].first, next.first});
		}
		if(cmp[i].first>0){
			ans.push_back({cmp[i].first, next.second});
		}
		if(next.first>0){
			ans.push_back({cmp[i].second, next.first});
		}
		ans.push_back({cmp[i].second, next.second});
	}

	for(auto &p: ans){
		if(p.first > p.second) swap(p.first, p.second);
	}
	sort(ans.begin(), ans.end());
	auto last = unique(ans.begin(), ans.end());
	ans.resize(last-ans.begin());

	cout << ans.size() << endl;
	for(auto p: ans){
		cout << p.first << " " << p.second << endl;
	}

	return 0;
}
