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

string X;

string eval(int i, int j){
	dbg(i, j);
	if(j-i<1) return "";
	int p=i;
	while(X[p]!='('&&p<j) p++;
	if(p==j) return X.substr(i, j-i);
	int q=p+1;
	int n=0;
	while(n>0||X[q]!=')'){
		if(X[q]=='(') n++;
		if(X[q]==')') n--;
		q++;
	}
	dbg(p, q);
	string e = eval(p+1, q);
	e += e;
	reverse(e.begin()+e.size()/2, e.end());
	return X.substr(i, p-i) + e + eval(q+1, j);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> X;

	cout << eval(0, X.size()) << endl;

	return 0;
}
