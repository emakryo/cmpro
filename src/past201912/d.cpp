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
	int n;
	cin >> n;
	vector<bool> b(n+1);
	int dup = -1;
	for(int i=0; i<n; i++){
		int a;
		cin >> a;
		if(b[a]) dup = a;
		b[a] = true;
	}
	if(dup<0){
		cout << "Correct" << endl;
		return 0;
	}

	int lack;
	for(int i=1; i<=n; i++){
		if(!b[i]) lack=i;
	}

	cout << dup << " " << lack << endl;

	return 0;
}
