#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, const char*>> any;
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
	Point operator+ (const Point &o) const { return Point(x+o.x, y+o.y); }
	Point& operator+= (const Point &o){ x += o.x; y += o.y; return *this; }
	Point operator- (const Point &o) const { return Point(x-o.x, y-o.y); }
	Point& operator-= (const Point &o){ x -= o.x; y -= o.y; return *this; }
	T dot(const Point &o) const { return x*o.x + y*o.y; }
	T det(const Point &o){ return x*o.y-y*o.x; }
	bool operator< (const Point &o) { return x<o.x || (x==o.x && y<o.y); };
};

typedef Point<long long> PLL;
vector<PLL> convex_hull(vector<PLL> &points){
	int n = points.size();
	sort(points.begin(), points.end());
	for(int i=0; i<n; i++) debug(any{"s", points[i].x, points[i].y});
	vector<PLL> lower(n), upper(n);
	int l = 0, r = 0;
	for(auto p: points){
		while(l>1 && (lower[l-1]-lower[l-2]).det(p-lower[l-1]) <= 0) l--;
		lower[l++] = p;
	}
	for(int i=0; i<l; i++) debug(any{"l", lower[i].x, lower[i].y});

	for(int j=points.size()-1; j>=0; j--){
		auto p = points[j];
		while(r>1 && (upper[r-1]-upper[r-2]).det(p-upper[r-1]) <= 0) r--;
		upper[r++] = p;
	}
	for(int i=0; i<r; i++) debug(any{"r", upper[i].x, upper[i].y});

	for(int j=1; j<r-1; j++) lower[l++] = upper[j];
	lower.resize(l);

	return lower;
}

int main(){
	int N;
	cin >> N;
	vector<ll> X(N), Y(N);
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i];
	vector<PLL> Ps(N);
	for(int i=0; i<N; i++) Ps[i] = PLL(X[i], Y[i]);

	vector<PLL> hull(1);
	for(int i=0; i<N; i++){
		int n_hull = hull.size();
		for(int j=0; j<n_hull; j++) hull.push_back(hull[j]+Ps[i]);
		for(auto p: hull) debug(any{i, p.x, p.y});
		debug(any{"="});
		hull = convex_hull(hull);
		for(auto p: hull) debug(any{i, p.x, p.y});
	}

	ll ans = 0;
	for(auto p: hull) ans = max(ans, p.dot(p));

	cout << setprecision(20) << sqrt(ans) << endl;

	return 0;
}
