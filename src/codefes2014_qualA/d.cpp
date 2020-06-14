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

ll rec(ll a, ll b, ll d, vector<bool> s, int k){
	dbg(b, d, s);
	if(d == 0){
		return abs(a-b);
	}

	int l = 0;
	for(bool si: s){
		if(si) l++;
	}

	int c = a/d%10;

	ll r = 1e18;
	if(l==k){
		if(a/d/10 > b/d/10){
			int e = 9;
			while(e>0&&!s[e]) e--;
			if(s[e]) r = min(r, rec(a, b+e*d, d/10, s, k));
		} else if(a/d/10 == b/d/10){
			int e = c;
			while(e>0&&!s[e]) e--;
			if(s[e]) r = min(r, rec(a, b+e*d, d/10, s, k));
			e = c+1;
			while(e<9&&!s[e]) e++;
			if(s[e]) r = min(r, rec(a, b+e*d, d/10, s, k));
		} else {
			int e = 0;
			while(e<9&&!s[e]) e++;
			if(s[e]) r = min(r, rec(a, b+e*d, d/10, s, k));
		}
	} else {
		if(a/d/10 > b/d/10){
			int e = 9;
			vector<bool> ns(s);
			ns[e] = true;
			r = min(r, rec(a, b+e*d, d/10, ns, k));
		}
		{
			vector<bool> ns(s);
			if(c!=0||b!=0) ns[c] = true;
			r = min(r, rec(a, b+c*d, d/10, ns, k));
		}
		if(l==k-1){
			if(c<9){
				vector<bool> ns(s);
				ns[c+1] = true;
				r = min(r, rec(a, b+(c+1)*d, d/10, ns, k));
			}
		}
		if(l==k-1){
			if(c>0){
				vector<bool> ns(s);
				if(c-1!=0||b!=0) ns[c-1] = true;
				r = min(r, rec(a, b+(c-1)*d, d/10, ns, k));
			}
		}
	}
	return r;
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	ll a;
	int k;
	cin >> a >> k;

	ll d = 1;
	while(a/d/10) d *= 10;
	vector<bool> s(10);

	cout << rec(a, 0, d, s, k) << endl;

	return 0;
}
