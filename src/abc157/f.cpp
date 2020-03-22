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
	friend Point operator+ (Point a, const Point &b) { a += b; return a; }
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
		complex<T> p = complex<T>(x, y) * complex<T>(o.x, o.y);
		return Point(p.real(), p.imag());
	}
	bool operator< (const Point &o) { return x<o.x || (x==o.x && y<o.y); };
};

typedef Point<double> P;
double dist2(P a, P b){
	return (a-b).dot(a-b);
}

vector<P> circles_intersections(P x1, double r1, P x2, double r2){
	P z = x2-x1;
	double d2 = dist2(z, P());
//	double cos = (r1*r1 + d2 - r2*r2)/(2*r1*sqrt(d2));
//	if(cos<-1 || 1<cos) return {};
//	P p(r1*cos, r1*sqrt(1-cos*cos));
//	vector<P> r{p, P(p.x, -p.y)};
//	for(P &t: r){
//		t = t.cp(z) / sqrt(d2) + x1;
//	}
//	return r;
	double a = (d2 + r1*r1 - r2*r2)/2;
	double b2 = d2 * r1*r1 - a*a;
	double c = d2;
	if(abs(b2) < 1e-10){
		return {P(a * z.x / c, a * z.y / c) + x1};
	}
	if(b2 < 0) return vector<P>();

	double b = sqrt(b2);
	return {P((a * z.x + z.y * b) / c,
			  (a * z.y - z.x * b) / c) + x1,
		   P((a * z.x - z.y * b) / c,
			 (a * z.y + z.x * b) / c) + x1};
}

int main(){
	int N, K;
	cin >> N >> K;
	vector<double> X(N), Y(N), C(N);
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i] >> C[i];

	double lb = 0, ub = 1000000;
	double eps = 1e-8;
	for(int l=0; l<100; l++){
		double med = (lb+ub)/2;
		bool ok = false;
		vector<P> candidates;
		for(int i=0; i<N; i++){
			for(int j=i+1; j<N; j++){
				vector<P> is = circles_intersections(P(X[i], Y[i]), med/C[i], P(X[j], Y[j]), med/C[j]);
				for(P p: is){
					candidates.push_back(p);
				}
			}
			candidates.push_back(P(X[i], Y[i]));
		}

		for(P p: candidates){
			int cnt = 0;
			for(int k=0; k<N; k++){
				if(C[k]*sqrt(dist2(P(X[k], Y[k]), p)) <= med+eps) cnt++;
			}
			if(cnt >= K){
				ok = true;
				debug(med, cnt, K, p.x, p.y);
			}
		}

		if(ok){
			ub = med;
		} else {
			lb = med;
		}
	}

	cout << setprecision(10) << lb << endl;

	return 0;
}
