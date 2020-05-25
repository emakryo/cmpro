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
	string s; cin >> s;
	vector<int> a(n);
	for(int i=0; i<n; i++) a[i] = s[i]-'1';

	vector<int> p2(n);
	for(int i=2; i<n; i*=2){
		for(int j=1; i*j<n; j++){
			p2[i*j]++;
		}
	}
	vector<int> fact_n2(n);
	for(int i=2; i<n; i++) fact_n2[i] = fact_n2[i-1]+p2[i];

	int n2 = 0;
	for(int i=0; i<n; i++){
		n2 += (a[i]%2)*(fact_n2[n-1]-fact_n2[i]-fact_n2[n-i-1]==0?1:0);
		dbg(i, fact_n2[n-1]-fact_n2[i]-fact_n2[n-i-1]);
	}
	dbg(n2);

	if(n2%2){
		cout << 1 << endl;
		return 0;
	}

	bool b1=false;
	for(int i=0; i<n; i++){
		if(a[i]==1) b1 = true;
	}

	if(b1){
		cout << 0 << endl;
		return 0;
	}

	int m2 = 0;
	for(int i=0; i<n; i++){
		m2 += (a[i]/2)*(fact_n2[n-1]-fact_n2[i]-fact_n2[n-i-1]==0?1:0);
	}

	if(m2%2){
		cout << 2 << endl;
	} else {
		cout << 0 << endl;
	}

	return 0;
}
