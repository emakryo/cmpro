#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
ll A[50];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	int amin=A[0], amax=A[0];
	int imin=0, imax=0;
	for(int i=0; i<N; i++){
		if(A[i]<amin){
			amin=A[i];
			imin=i;
		}
		if(A[i]>amax){
			amax=A[i];
			imax=i;
		}
	}

	vector<pair<int, int>> ans;
	if(abs(amin) < abs(amax)){
		ans.push_back({imax, 1});
		ans.push_back({imax, 1});
		for(int i=2; i<N; i++){
			ans.push_back({i-1, i});
			ans.push_back({i-1, i});
		}
	} else {
		ans.push_back({imin, N-2});
		ans.push_back({imin, N-2});
		for(int i=N-3; i>=0; i--){
			ans.push_back({i+1, i});
			ans.push_back({i+1, i});
		}
	}

	cout << ans.size() << endl;
	for(int i=0; i<ans.size(); i++){
		cout << ans[i].first+1 << " " << ans[i].second+1 << endl;
	}

	return 0;
}
