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
	int k, n;
	cin >> k >> n;
	vector<string> v(n), w(n);
	for(int i=0; i<n; i++) cin >> v[i] >> w[i];

	for(int s=0; s<(1<<(2*k)); s++){
		bool ok = true;
		vector<int> ls(k);
		for(int i=0; i<k; i++){
			int a = s>>(2*i)&3;
			ls[i] = a;
			if(a==0) ok = false;
		}
		if(!ok) continue;

		vector<string> x(k);
		for(int i=0; i<n; i++){
			int p=0;
			for(int j=0; j<v[i].size(); j++){
				int a = v[i][j]-'1';
				int l = ls[a];
				string y=w[i].substr(p, l);
				p+=l;
				if(p>w[i].size()){
					ok=false;
					break;
				}
				if(x[a]==""){
					x[a]=y;
				} else if(x[a]!=y){
					ok=false;
				}
				if(!ok) break;
			}
			if(p!=w[i].size()){
				ok=false;
			}
			if(!ok) break;
		}

		if(ok){
			for(string y: x){
				cout << y << endl;
			}
			return 0;
		}
	}
	return 0;
}
