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

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
	for(int i=0; i<v.size(); i++) is >> v[i];
	return is;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int n;
	ll d;
	cin >> n >> d;

	map<int, int> cnt;
	for(int p: {2, 3, 5}){
		while(d%p==0){
			cnt[p]++;
			d /= p;
		}
	}

	if(d>1){
		cout << 0 << endl;
		return 0;
	}

	vector<vector<vector<double>>> dp(201, vector<vector<double>>(101, vector<double>(101)));
	vector<vector<vector<double>>> next(201, vector<vector<double>>(101, vector<double>(101)));
	dp[0][0][0] = 1;
	for(int i=0; i<n; i++){
		for(int j2=0; j2<201; j2++) for(int j3=0; j3<101; j3++) for(int j5=0; j5<101; j5++){
			next[j2][j3][j5] = dp[j2][j3][j5];
		}
		for(int j2=0; j2<201; j2++) for(int j3=0; j3<101; j3++) for(int j5=0; j5<101; j5++){
			if(j2+1<201) next[j2+1][j3][j5] += dp[j2][j3][j5];
			if(j3+1<101) next[j2][j3+1][j5] += dp[j2][j3][j5];
			if(j2+2<201) next[j2+2][j3][j5] += dp[j2][j3][j5];
			if(j5+1<101) next[j2][j3][j5+1] += dp[j2][j3][j5];
			if(j2+1<201&&j3+1<101) next[j2+1][j3+1][j5] += dp[j2][j3][j5];
		}
		swap(dp, next);
	}

	double ans = 0;
	int p2 = cnt[2];
	int p3 = cnt[3];
	int p5 = cnt[5];
	for(int j2=0; j2<201; j2++) for(int j3=0; j3<101; j3++) for(int j5=0; j5<101; j5++){
		if(j2>=p2 && j3>=p3 && j5>=p5) ans += dp[j2][j3][j5];
	}

	for(int i=0; i<n; i++) ans /= 6;

	cout << ans << endl;

	return 0;
}
