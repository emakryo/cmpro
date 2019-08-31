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
int N, K;

int main(){
	cin >> N >> K;

	if(K > (N-1)*(N-2)/2){
		cout << -1 << endl;
		return 0;
	}

	vector<pair<int, int> > ans;
	for(int i=1; i<N; i++){
		ans.push_back({i, N});
	}

	int n=0;
	for(int i=0; i<N-1; i++){
		if(n>=(N-1)*(N-2)/2-K) break;
		for(int j=i+1; j<N-1; j++){
			if(n>=(N-1)*(N-2)/2-K) break;
			ans.push_back({i+1, j+1});
			n++;
		}
	}

	cout << ans.size() << endl;
	for(auto p: ans){
		cout << p.first << " " << p.second << endl;
	}

	return 0;
}
