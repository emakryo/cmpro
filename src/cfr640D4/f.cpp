#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
	string sep = " ";
	if(v.size()) os << v[0];
	for(int i=1; i<v.size(); i++) os << sep << v[i];
	return os;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

string solve(){
	vector<int> n(3);
	for(int i=0; i<3; i++) cin >> n[i];

	string s;
	if(n[0]>0||n[1]>0){
		s += '0';
	}

	while(n[0]>0){
		n[0]--;
		s+='0';
	}

	if(n[1]==0&&n[2]==0) return s;

	if(s.size()>0) n[1]--;
	s+='1';
	while(n[2]>0){
		n[2]--;
		s+='1';
	}
	dbg(n, s);

	int p = 1;
	while(n[1]>0){
		p=1-p;
		n[1]--;
		s+='0'+p;
	}
	return s;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for(int i=0; i<t; i++) cout << solve() << endl;;
	return 0;
}
