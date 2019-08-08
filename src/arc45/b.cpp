#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Mmax = 1e5;
int N, M, S[Mmax], T[Mmax];

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++) cin >> S[i] >> T[i];

	vector<pair<int, int>> xs;
	for(int i=0; i<M; i++){
		xs.push_back({S[i], i});
		xs.push_back({T[i], i+M});
	}
	sort(xs.begin(), xs.end());

	vector<bool> must(M);
	set<int> current;

	int j=0;
	for(int i=1; i<=N; i++){
		while(xs[j].first==i && xs[j].second<M){
			current.insert(xs[j].second);
			j++;
		}
		if(current.size()==1) must[*current.begin()] = true;
		while(xs[j].first==i){
			current.erase(xs[j].second-M);
			j++;
		}
	}

	vector<int> ans;
	for(int i=0; i<M; i++){
		if(!must[i]) ans.push_back(i);
	}

	cout << ans.size() << endl;
	for(int i=0; i<ans.size(); i++){
		cout << ans[i]+1 << endl;
	}

	return 0;
}
