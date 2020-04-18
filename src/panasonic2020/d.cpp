#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> anys;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(anys{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int N;
	cin >> N;

	vector<string> ans{"a"};

	for(int i=1; i<N; i++){
		vector<string> next;
		for(auto s: ans){
			set<char> cs;
			for(char c: s){
				cs.insert(c);
			}
			for(char c='a'; c<='a'+cs.size(); c++){
				next.push_back(s + c);
			}
		}
		ans = next;
	}

	for(auto s: ans){
		cout << s << endl;
	}

	return 0;
}
