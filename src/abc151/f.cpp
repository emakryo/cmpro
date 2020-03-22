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

int main() {
	int N;
	cin >> N;
	vector<int> X(N), Y(N);
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i];

	double lb = 0, ub = 100000;
	for(int l=0; l<100; l++){
		double med = (lb+ub)/2;
		debug(med);
		vector<P> cands;
		for(int i=0; i<N; i++){
			for(int j=i+1; j<N; j++){
				for(P p: circles_intersections(P(X[i], Y[i]), med, P(X[j], Y[j]), med)){
					cands.push_back(p);
				}
			}
			cands.push_back(P(X[i], Y[i]));
		}

		bool ok = false;
		for(P p: cands){
			bool ok_ = true;
			for(int i=0; i<N; i++){
				if(sqrt(dist2(P(X[i], Y[i]), p)) > med+1e-8) ok_ = false;
			}
			ok = ok || ok_;
		}

		if(ok){
			ub = med;
		} else {
			lb = med;
		}
	}

	cout << setprecision(10) << ub << endl;
	return 0;
}
