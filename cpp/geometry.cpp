#include<bits/stdc++.h>

template<typename T>
struct Point {
	T x, y;
	Point(T x=0, T y=0):x(x), y(y) {}
	Point(std::pair<T, T> p): x(p.first), y(p.second) {}
	Point& operator+= (const Point &o){ x += o.x; y += o.y; return *this; }
	friend Point operator+ (Point x, const Point &y) { x += y; return x; }
	Point& operator-= (const Point &o){ x -= o.x; y -= o.y; return *this; }
	friend Point operator- (Point x, const Point &y) { x -= y; return x; }
	Point& operator*= (const T &a) { x *= a, y *= a; return *this; }
	friend Point operator* (const T a, Point x) { x *= a; return x; }
	Point& operator/= (const T &a) { x /= a, y /= a; return *this; }
	friend Point operator/ (Point x, const T a) { x /= a; return x; }
	T dot(const Point &o) const { return x*o.x+y*o.y; }
	T det(const Point &o){ return x*o.y-y*o.x; }
	// complex product
	Point cp(const Point &o) {
		std::complex<T> p = std::complex<T>(x, y) * std::complex<T>(o.x, o.y);
		return Point(p.real(), p.imag());
	}
	bool operator< (const Point &o) { return x<o.x || (x==o.x && y<o.y); };
};

template<typename T>
std::ostream& operator<<(std::ostream &os, Point<T> &p){
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

typedef Point<long long> PLL;
std::vector<PLL> convex_hull(std::vector<PLL> &points){
	int n = points.size();
	std::sort(points.begin(), points.end());
	std::vector<PLL> lower(n), upper(n);
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

typedef Point<double> P;
double dist2(P a, P b){
	return (a-b).dot(a-b);
}

// 外心, not tested well
P circumcenter(P a, P b, P c){
	double x = dist2(b, c);
	double y = dist2(a, c);
	double z = dist2(a, b);

	double p = x*(y+z-x);
	double q = y*(x+z-y);
	double r = z*(y+x-z);

	if(p+q+r < 1e-5){
		if(x >= y && x >= z){
			return 0.5 * (b + c);
		} else if(y >= x && y >= z){
			return 0.5 * (a + c);
		} else {
			return 0.5 * (a + b);
		}
	} else {
		return (p*a + q*b + r*c) / (p + q + r);
	}
}

std::vector<P> circles_intersections(P x1, double r1, P x2, double r2){
	P z = x2-x1;
	double d2 = dist2(z, P());
	double a = (d2 + r1*r1 - r2*r2)/2;
	double b2 = d2 * r1*r1 - a*a;
	double c = d2;
	if(abs(b2) < 1e-10){
		return {P(a * z.x / c, a * z.y / c) + x1};
	}
	if(b2 < 0) return std::vector<P>();

	double b = sqrt(b2);
	return {P((a * z.x + z.y * b) / c,
			  (a * z.y - z.x * b) / c) + x1,
		   P((a * z.x - z.y * b) / c,
			 (a * z.y + z.x * b) / c) + x1};
}
