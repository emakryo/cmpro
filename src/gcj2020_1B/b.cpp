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
void debug_(){ cerr << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cerr << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

enum Response {
	CENTER,
	HIT,
	MISS,
	WRONG
};

Response query(int x, int y){
	cout << x << " " << y << endl;;
	string r;
	cin >> r;
	dbg(r, x, y);
	if(r=="CENTER") return CENTER;
	if(r=="HIT") return HIT;
	if(r=="MISS") return MISS;
	if(r=="WRONG") return WRONG;
}

bool solve(int a, int b){
	int hx, hy;
	int d = 1e9/2;
	int dx[]={-d, 0, d};
	int dy[]={-d, 0, d};
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			Response r = query(dx[i], dy[j]);
			if(r == CENTER){
				return true;
			} else if(r == WRONG){
				return false;
			} else if(r == HIT){
				hx = dx[i];
				hy = dy[j];
			}
		}
	}

	int lb, ub;
	lb = -1e9-5;
	ub=hx;
	while(ub-lb>1){
		int med = (ub+lb)/2;
		Response r = query(med, hy);
		if(r == CENTER){
			return true;
		} else if(r == WRONG){
			return false;
		} else if(r == HIT){
			ub = med;
		} else {
			lb = med;
		}
	}
	int lx = ub;

	lb = hx;
	ub = 1e9+5;
	while(ub-lb>1){
		int med = (ub+lb)/2;
		Response r = query(med, hy);
		if(r == CENTER){
			return true;
		} else if(r == WRONG){
			return false;
		} else if(r == HIT){
			lb = med;
		} else {
			ub = med;
		}
	}
	int rx = lb;

	lb = -1e9-5;
	ub = hy;
	while(ub-lb>1){
		int med = (ub+lb)/2;
		Response r = query(hx, med);
		if(r == CENTER){
			return true;
		} else if(r == WRONG){
			return false;
		} else if(r == HIT){
			ub = med;
		} else {
			lb = med;
		}
	}
	int by = ub;

	lb = hy;
	ub = 1e9+5;
	while(ub-lb>1){
		int med = (ub+lb)/2;
		Response r = query(hx, med);
		if(r == CENTER){
			return true;
		} else if(r == WRONG){
			return false;
		} else if(r == HIT){
			lb = med;
		} else {
			ub = med;
		}
	}
	int ty = lb;

	Response r = query((lx+rx)/2, (by+ty)/2);
	return r == CENTER;

}

int main() {
	ios_base::sync_with_stdio(false);
	int t, a, b;
	cin >> t >> a >> b;
	for(int i=0; i<t; i++){
		if(!solve(a, b)) break;
	}
	return 0;
}
