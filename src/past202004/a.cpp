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

int parse(string x){
	if(x[0]=='B'){
		return -int(x[1]-'1');
	} else {
		return x[0]-'0';
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	string s, t;
	cin >> s >> t;
	cout << abs(parse(s)-parse(t)) << endl;
	return 0;
}
