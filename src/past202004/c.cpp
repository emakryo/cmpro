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

int main() {
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	vector<string> s(n);
	for(int i=0; i<n; i++) cin >> s[i];

	for(int i=n-2; i>=0; i--){
		for(int j=1; j<2*n-2; j++){
			dbg(i, j);
			if(s[i][j]=='.') continue;
			if(s[i+1][j-1]=='X'||s[i+1][j]=='X'||s[i+1][j+1]=='X') s[i][j]='X';
		}
	}

	for(int i=0; i<n; i++) cout << s[i] << endl;
	return 0;
}
