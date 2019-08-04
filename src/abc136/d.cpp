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
string S;

int main(){
	cin >> S;

	int N=S.size();

	vector<pair<int, int> > rl;
	vector<int> rlidx;
	pair<int, int> cur = {1, 0};
	for(int i=1; i<N; i++){
		if(S[i-1]=='R'){
			if(S[i]=='R') cur.first++;
			else{
				cur.second++;
				rlidx.push_back(i);
			}
		} else {
			if(S[i]=='R'){
				rl.push_back(cur);
				cur = {1, 0};
			} else cur.second++;
		}
	}
	rl.push_back(cur);

	vector<int> ans(N);
	for(int i=0; i<rl.size(); i++){
		ans[rlidx[i]-1] = (rl[i].first+1)/2 + rl[i].second/2;
		ans[rlidx[i]] = rl[i].first/2 + (rl[i].second+1)/2;
	}

	for(int i=0; i<N; i++){
		cout << ans[i] << (i==N-1?'\n':' ');
	}

	return 0;
}
