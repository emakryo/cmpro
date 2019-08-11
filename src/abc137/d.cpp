#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, M;
const int Nmax = 1e5;
vector<pair<int, int>> BA;

int main(){
	cin >> N >> M;
	for(int i=0; i<N; i++){
		int a, b;
		cin >> a >> b;
		BA.push_back({b, a});
	}
	sort(BA.begin(), BA.end());
	reverse(BA.begin(), BA.end());

	vector<int> nextl;
	for(int i=0; i<M; i++) nextl.push_back(i);
	ll ans = 0;
	for(int i=0; i<N; i++){
		int b = BA[i].first;
		int a = BA[i].second;
		vector<int> step;
		int k=M-a;
		while(k>=0&&nextl[k]!=k){
			step.push_back(k);
			k=nextl[k];
		}
		for(auto j: step){
			nextl[j] = k;
		}
		if(k<0) continue;

		ans += b;
		//cout << a << " " << b << " " <<nextl[k] << endl;
		nextl[k] = k-1;
	}

	cout << ans << endl;

	return 0;
}
