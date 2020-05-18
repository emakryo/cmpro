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

	int a, b, h, m;
	cin >> a >> b >> h >> m;
	double al = 2*M_PI*(60*h+m)/(12*60);
	double be = 2*M_PI*m/60;
	
	double ax = a*cos(al);
	double ay = a*sin(al);
	double bx = b*cos(be);
	double by = b*sin(be);
	cout << setprecision(20);
	cout << sqrt((ax-bx)*(ax-bx) + (ay-by)*(ay-by)) << endl;
	return 0;
}
