#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

ll canonical(const vector<int> &c){
	ll x = 1LL<<62;
	for(int i=0; i<4; i++){
		ll t = 0;
		for(int j=0; j<4; j++){
			t = (t<<10) + c[(i+j)%4];
		}
		x = min(x, t);
	}
	return x;
}

int count_greater(const vector<int> &v, int n, int m){
	auto it = lower_bound(v.begin(), v.end(), n);
	int x = v.end()-it;
	if(x>0&&*it==n) x--;
	if(binary_search(v.begin(), v.end(), m)) x--;
	return x;
}

int mul(ll x){
	ll c0 = (x>>30)&((1<<10)-1);
	ll c1 = (x>>20)&((1<<10)-1);
	ll c2 = (x>>10)&((1<<10)-1);
	ll c3 = (x>>0)&((1<<10)-1);
	if(c0==c1&&c1==c2&&c2==c3) return 4;
	if(c0==c2&&c1==c3) return 2;
	else return 1;
}

int main(){
	int N;
	cin >> N;
	vector<vector<int>> C(N, vector<int>(4));
	for(int i=0; i<N; i++) for(int k=0; k<4; k++) cin >> C[i][k];

	map<ll, vector<int>> faces;
	for(int i=0; i<N; i++){
		faces[canonical(C[i])].push_back(i);
	}

	ll ans = 0;
	for(int i=0; i<N; i++) for(int j=i+1; j<N; j++) for(int k=0; k<4; k++){
		ll side[4];
		for(int l=0; l<4; l++){
			side[l] = canonical({C[i][l], C[j][(k+3-l+1)%4], C[j][(k+3-l)%4], C[i][(l+1)%4]});
		}
		sort(side, side+4);
		ll x[4];
		ll a = 1;
		for(int l=0; l<4; l++){
			x[l] = count_greater(faces[side[l]], i, j);
			a *= mul(side[l]);
		}
		if(side[0]==side[1]&&side[1]==side[2]&&side[2]==side[3]){
			a *= x[0]*(x[0]-1)*(x[0]-2)*(x[0]-3);
		} else if(side[0]==side[1]&&side[1]==side[2]){
			a *= x[0]*(x[0]-1)*(x[0]-2)*x[3];
		} else if(side[1]==side[2]&&side[2]==side[3]){
			a *= x[0]*x[1]*(x[1]-1)*(x[1]-2);
		} else if(side[0]==side[1]&&side[2]==side[3]){
			a *= x[0]*(x[0]-1)*x[2]*(x[2]-1);
		} else if(side[0]==side[1]){
			a *= x[0]*(x[0]-1)*x[2]*x[3];
		} else if(side[1]==side[2]){
			a *= x[0]*x[1]*(x[1]-1)*x[3];
		} else if(side[2]==side[3]){
			a *= x[0]*x[1]*x[2]*(x[2]-1);
		} else {
			a *= x[0]*x[1]*x[2]*x[3];
		}
		debug(any{i, j, k, a, x[0], x[1], x[2], x[3]});
		ans += a;
	}

	cout << ans << endl;

	return 0;
}
