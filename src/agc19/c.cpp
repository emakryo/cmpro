#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
ll Xs, Ys, Xg, Yg;
int N;
const int Nmax = 2e5;
const double PI = 3.1415926535897;
ll X[Nmax], Y[Nmax];

template <class T>
class SegmentTree{
	vector<T> v;
	T def;
	int n;
	public:
	template<class I>
	SegmentTree(I first, I last, T default_value){
		n = 1;
		def = default_value;
		while(n < last-first) n <<= 1;
		v = vector<T>(2*n-1, default_value);
		copy(first, last, v.begin()+n-1);
		for(int i=n-2; i>=0; i--) v[i] = merge(v[2*i+1], v[2*i+2]);
	}
	SegmentTree(int length, T default_value){
		n = 1;
		def = default_value;
		while(n < length) n <<= 1;
		v = vector<T>(2*n-1, default_value);
		for(int i=n-2; i>=0; i--) v[i] = merge(v[2*i+1], v[2*i+2]);
	}
	SegmentTree(vector<T> initial_data, T default_value):
	SegmentTree(initial_data.begin(), initial_data.end(), default_value){}
	void update(int idx, T val){
		idx += n-1;
		v[idx] = val;
		while(idx > 0){
			idx = (idx-1)/2;
			v[idx] = merge(v[2*idx+1], v[2*idx+2]);
		}
	}
	T q(int a, int b, int k, int l, int r){
		if(a<=l&&r<=b) return v[k];
		if(b<=l||r<=a) return def;
		return merge(q(a, b, 2*k+1, l, (l+r)/2), q(a, b, 2*k+2, (l+r)/2, r));
	}
	T query(int a, int b){
		return q(a, b, 0, 0, n);
	}
	T merge(T left, T right);
};

template <>
int SegmentTree<int>::merge(int a, int b){
	return max(a, b);
}

int main(){
	cin >> Xs >> Ys >> Xg >> Yg;
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> X[i] >> Y[i];
	}

	vector<pair<ll, int> > xs, ys;
	for(int i=0; i<N; i++){
		if(Xs <= X[i] && X[i] <= Xg){
			if(Ys <= Y[i] && Y[i] <= Yg){
				xs.push_back({X[i], i});
				ys.push_back({Y[i], i});
			} else if(Yg <= Y[i] && Y[i] <= Ys){
				xs.push_back({X[i], i});
				ys.push_back({-Y[i], i});
			}
		} else if(Xg <= X[i] && X[i] <= Xs){
			if(Ys <= Y[i] && Y[i] <= Yg){
				xs.push_back({-X[i], i});
				ys.push_back({Y[i], i});
			} else if(Yg <= Y[i] && Y[i] <= Ys){
				xs.push_back({-X[i], i});
				ys.push_back({-Y[i], i});
			}
		}
	}
	if(Xs > Xg){
		Xs = -Xs;
		Xg = -Xg;
	}
	if(Ys > Yg){
		Ys = -Ys;
		Yg = -Yg;
	}

	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());

	vector<int> xc(N), yc(N);

	for(int i=0; i<xs.size(); i++){
		xc[xs[i].second] = i;
		yc[ys[i].second] = i;
	}

	cout << setprecision(20);
	if(Xs == Xg){
		auto it = lower_bound(xs.begin(), xs.end(), make_pair(Xs, 0));
		double ans = 100*abs(Ys-Yg);
		if(it != xs.end() && it->first == Xs){
			ll yi = Y[it->second];
			if((Ys < yi && yi < Yg) || (Ys < -yi && -yi < Yg)){
				ans += 10*PI-20;
			}
		}
		cout << ans << endl;
		return 0;
	}

	if(Ys == Yg){
		auto it = lower_bound(ys.begin(), ys.end(), make_pair(Ys, 0));
		double ans = 100*abs(Xs-Xg);
		if(it != ys.end() && it->first == Ys){
			ll xi = X[it->second];
			if((Xs < xi && xi < Xg) || (Xs < -xi && -xi < Xg)){
				ans += 10*PI-20;
			}
		}
		cout << ans << endl;
		return 0;
	}
	//cout << xs.size() << endl;

	SegmentTree<int> st_max(N+1, 0);
	for(auto p: xs){
		//cout << p.first << " " << yc[p.second] << " " << st_max.query(0, yc[p.second]) << endl;
		st_max.update(yc[p.second], st_max.query(0, yc[p.second]) + 1);
	}

	int k = st_max.query(0, N);
	//cout << k << endl;

	if(k==min(abs(Xs-Xg), abs(Ys-Yg))+1){
		cout << 100*(abs(Xs-Xg) + abs(Ys-Yg)) - (k-1) * (20 - 5*PI) + (10*PI - 20) << endl;
	} else {
		cout << 100*(abs(Xs-Xg) + abs(Ys-Yg)) - k * (20 - 5*PI) << endl;
	}

	return 0;
}
