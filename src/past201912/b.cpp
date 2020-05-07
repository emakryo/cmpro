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
	int a;
	cin >> a;
	for(int i=0; i<n-1; i++){
		int b;
		cin >> b;
		if(a==b){
			cout << "stay" << endl;
		} else if(a<b){
			cout << "up " << b-a << endl;
		} else {
			cout << "down " << a-b << endl;
		}
		a = b;
	}
	return 0;
}
