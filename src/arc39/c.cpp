#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int K;
	cin >> K;
	string S;
	cin >> S;

	map<pair<int, int>, int> left, right, up, down;
	left[{0, 0}] = -1;
	right[{0, 0}] = 1;
	up[{0, 0}] = 1;
	down[{0, 0}] = -1;
	int x=0, y=0;
	for(int i=0; i<K; i++){
		int nx = x;
		int ny = y;
		if(S[i]=='L'){
			while(left.count({nx, ny})>0) nx = left[{nx, ny}];
			right[{nx, ny}] = right.count({x+1, ny})>0?right[{x+1, ny}]:x+1;
			left[{nx, ny}] = nx-1;
			up[{nx, ny}] = up.count({nx, y+1})>0?up[{nx, ny+1}]:ny+1;
			down[{nx, ny}] = down.count({nx, y-1})>0?down[{nx, ny-1}]:ny-1;

			left[{x, y}] = nx-1;
		} else if(S[i]=='R'){
			while(right.count({nx, ny})>0) nx = right[{nx, ny}];
			right[{nx, ny}] = nx+1;
			left[{nx, ny}] = left.count({x-1, ny})>0?left[{x-1, ny}]:x-1;
			up[{nx, ny}] = up.count({nx, ny+1})>0?up[{nx, ny+1}]:ny+1;
			down[{nx, ny}] = down.count({nx, ny-1})>0?down[{nx, ny-1}]:ny-1;

			right[{x, y}] = nx+1;
		} else if(S[i]=='U'){
			while(up.count({nx, ny})>0) ny = up[{nx, ny}];
			right[{nx, ny}] = right.count({nx+1, ny})>0?right[{nx+1, ny}]:nx+1;
			left[{nx, ny}] = left.count({nx-1, ny})>0?left[{nx-1, ny}]:nx-1;
			up[{nx, ny}] = ny+1;
			down[{nx, ny}] = down.count({nx, y-1})>0?down[{nx, y-1}]:y-1;

			up[{x, y}] = ny+1;
		} else {
			while(down.count({nx, ny})>0) ny = down[{nx, ny}];
			right[{nx, ny}] = right.count({nx+1, ny})>0?right[{nx+1, ny}]:nx+1;
			left[{nx, ny}] = left.count({nx-1, ny})>0?left[{nx-1, ny}]:nx-1;
			up[{nx, ny}] = up.count({nx, y+1})>0?up[{nx, y+1}]:y+1;
			down[{nx, ny}] = ny-1;

			down[{x, y}] = ny-1;
		}
		x = nx;
		y = ny;

		debug(x, y, left[{x, y}], right[{x, y}], up[{x, y}], down[{x, y}]);
	}
	cout << x << " " << y << endl;

	return 0;
}
