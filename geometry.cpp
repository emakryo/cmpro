#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct Point {
	T x, y;
	Point(T x=0, T y=0):x(x), y(y) {}
	Point(pair<T, T> p): x(p.first), y(p.second) {}
	Point operator+ (const Point &o) const { return Point(x+o.x, y+o.y); }
	Point& operator+= (const Point &o){ x += o.x; y += o.y; return *this; }
	Point operator- (const Point &o) const { return Point(x-o.x, y-o.y); }
	Point& operator-= (const Point &o){ x -= o.x; y -= o.y; return *this; }
	T dot(const Point &o) const { return x*o.x+y*o.y; }
	T det(const Point &o){ return x*o.y-y*o.x; }
	bool operator< (const Point &o) { return x<o.x || (x==o.x && y<o.y); };
};

typedef Point<long long> PLL;
vector<PLL> convex_hull(vector<PLL> &points){
	int n = points.size();
	sort(points.begin(), points.end());
	vector<PLL> lower(n), upper(n);
	int l = 0, r = 0;
	for(auto p: points){
		while(l>1 && (lower[l-1]-lower[l-2]).det(p-lower[l-1]) <= 0) l--;
		lower[l++] = p;
	}

	for(int j=points.size()-1; j>=0; j--){
		auto p = points[j];
		while(r>1 && (upper[r-1]-upper[r-2]).det(p-upper[r-1]) <= 0) r--;
		upper[r++] = p;
	}

	for(int j=1; j<r-1; j++) lower[l++] = upper[j];
	lower.resize(l);

	return lower;
}
