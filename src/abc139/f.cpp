#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

template<typename T>
struct Point {
	T x, y;
	Point(T x=0, T y=0):x(x), y(y) {}
	Point(pair<T, T> p): x(p.first), y(p.second) {}
	Point operator + (const Point &o){ return Point(x+o.x, y+o.y); }
	Point& operator += (const Point &o){ x += o.x; y += o.y; return *this; }
	Point operator - (const Point &o){ return Point(x-o.x, y+o.y); }
	Point& operator -= (const Point &o){ x -= o.x; y -= o.y; return *this; }
	T dot(const Point &o){ return x*o.x + y*o.y; }
	T det(const Point &o){ return x*o.y-y*o.x; }
};


int main(){
	int N;
	cin >> N;
	vector<ll> X(N), Y(N);
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i];
	vector<Point<ll>> Ps(N);
	for(int i=0; i<N; i++) Ps[i] = Point<ll>(X[i], Y[i]);

	vector<pair<double, int>> rads;
	for(int i=0; i<N; i++){
		double rad;
		if(X[i]>0) rad=atan((double)Y[i]/X[i]);
		else if(X[i]<0) rad=atan((double)Y[i]/X[i])+M_PI;
		else if(X[i]==0 && Y[i]>0) rad=M_PI/2;
		else rad=-M_PI/2;
		rads.push_back({rad, i});
	}

	sort(rads.begin(), rads.end());
	ll ans = 0;
	for(int i=0; i<N; i++){
		Point<ll> sum;
		for(int j=0; j<N; j++){
			sum += Ps[rads[(i+j)%N].second];
			debug(any{i, j, sum.x, sum.y});
			ans = max(ans, sum.dot(sum));
		}
	}

	cout << setprecision(20) << sqrt(ans) << endl;

	return 0;
}
