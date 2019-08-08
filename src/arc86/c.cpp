#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
	int N, K;
	map<int, int> cnt;
	cin >> N >> K;
	for(int i=0; i<N; i++){
		int a;
		cin >> a;
		cnt[a]++;
	}

	vector<int> c;
	for(auto p: cnt){
		c.push_back(p.second);
	}
	sort(c.begin(), c.end());

	int ans = 0;
	for(int i=0; i<max(0, (int)c.size()-K); i++){
		ans += c[i];
	}
	cout << ans << endl;

	return 0;
}
