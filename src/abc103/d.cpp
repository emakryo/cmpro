#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<set>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Mmax = 1e5;
int N, M, A[Mmax], B[Mmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++) cin >> A[i] >> B[i];

	vector<pair<int, int>> xs;
	for(int i=0; i<M; i++){
		xs.push_back({2*B[i], i});
		xs.push_back({2*A[i]+1, i});
	}
	sort(xs.begin(), xs.end());

	int ans = 0;
	set<int> current;
	for(int i=0; i<2*M; i++){
		if(xs[i].first%2){
			current.insert(xs[i].second);
		} else{
			auto it = current.find(xs[i].second);
			if(it == current.end()) continue;
			ans++;
			current.clear();
		}
	}

	cout << ans << endl;

	return 0;
}
