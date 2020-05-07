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
	string s;
	cin >> s;
	int ans = 0;
	int d=100;
	for(int i=0; i<3; i++){
		if('0'<=s[i]&&s[i]<='9') ans += (s[i]-'0')*d;
		else {
			cout << "error" << endl;
			return 0;
		}
		d /= 10;
	}
	cout << 2*ans << endl;

	return 0;
}
