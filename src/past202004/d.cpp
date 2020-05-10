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
	set<string> x;
	for(int p=1; p<=min(3, (int)s.size()); p++){
		for(int i=0; i<s.size()-p+1; i++){
			dbg(i, p, s.size()-p+1);
			string t = s.substr(i, p);
			for(int b=0; b<(1<<p); b++){
				string u(t);
				for(int j=0; j<p; j++){
					if((b>>j&1)==0) continue;
					u[j] = '.';
				}
				dbg(i, p, t, b, u);
				x.insert(u);
			}
		}
	}

	cout << x.size() << endl;
	return 0;
}
