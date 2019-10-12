#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int N, C;
	cin >> N >> C;
	vector<vector<pair<int, int>>> program(C+1);
	for(int i=0; i<N; i++){
		int s,t,c;
		cin >> s >> t >> c;
		program[c].push_back({s, t});
	}

	vector<pair<int, int>> ts;
	for(int c=1; c<=C; c++){
		if(program[c].size()==0) continue;
		sort(program[c].begin(), program[c].end());
		auto p = program[c][0];
		for(int j=1; j<program[c].size(); j++){
			if(p.second == program[c][j].first){
				p.second = program[c][j].second;
			} else {
				ts.push_back({p.first, -c});
				ts.push_back({p.second, c});
				p = program[c][j];
			}
		}
		ts.push_back({p.first, -c});
		ts.push_back({p.second, c});
	}

	sort(ts.begin(), ts.end());

	int ans = 0;
	set<int> current;
	for(int i=0; i<ts.size(); i++){
		debug(ts[i].first, ts[i].second);
		if(ts[i].second < 0){
			current.insert(-ts[i].second);
			ans = max(ans, (int)current.size());
		} else {
			current.erase(ts[i].second);
		}
	}
	cout << ans << endl;

	return 0;
}
