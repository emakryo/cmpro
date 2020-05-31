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
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

int rec(vector<int> &v, int k){
	if(k==0){
		dbg(v);
		return 1;
	}
	int r = 0;
	for(int i=0; i<3; i++){
		int j=v.size()-1;
		int ok = true;
		dbg(k, i, j, (int)v.size()-1-i);
		while(j>=0&&j>=(int)v.size()-1-i){
			dbg(k, i, j, (int)v.size()-1-i, v[j]);
			if(v[j]==i) ok=false;
			j--;
		}
		if(!ok) continue;
		v.push_back(i);
		r += rec(v, k-1);
		v.pop_back();
	}
	return r;
}

int rec0(vector<vector<int>> &v, int k){
	int n = v.size();
	int m = v[0].size();
	int i = k%n;
	int j = k/n;

	if(k==n*m) return 1;

	int r = 0;
	for(int a=1; a<=3; a++){
		bool ok = true;
		for(int l=0; l<a; l++){
			if(i-l-1<0) break;
			if(v[i-l-1][j]==a) ok=false;
		}
		for(int l=0; l<a; l++){
			if(j-l-1<0) break;
			if(v[i][j-l-1]==a) ok=false;
		}
		if(!ok) continue;
		v[i][j] = a;
		r += rec0(v, k+1);
	}

	return r;
}


int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int m, n; cin >> m >> n;

	if(n<4&&m<4){
		vector<vector<int>> v(n, vector<int>(m));
		cout << rec0(v, 0) << endl;
		return 0;
	}

	int k = m+n-1;
	if(k>8){
		k = (k-8)%4+8;
	}

	vector<int> v;
	if(n==1||m==1){
		cout << rec(v, k) << endl;
	} else {
		cout << 2*rec(v, k) << endl;
	}
	return 0;
}
