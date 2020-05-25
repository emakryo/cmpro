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

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;
	int n; cin >> n;

	vector<double> ans(n+1);

	vector<vector<double>> comb(105, vector<double>(105));
	comb[0][0]=1;
	comb[1][0]=1;
	comb[1][1]=1;
	for(int i=0; i<105; i++){
		comb[i][0] = 1;
		comb[i][i] = 1;
	}
	for(int i=2; i<105; i++){
		for(int j=1; j<i; j++){
			comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
		}
	}
	vector<double> pow3(105);
	pow3[0] = 1;
	for(int i=1; i<105; i++) pow3[i] = pow3[i-1]*3;

	for(int i=2; i<=n; i++){
		double a = 0;
		double b = 0;
		for(int p=0; p<=i; p++){
			for(int q=0; p+q<=i; q++){
				int r = i-p-q;
				double m = comb[i][p]*comb[i-p][q];
				if(p==q&&q==r){
					a += m;
				} else if(p==q&&q==0||q==r&&r==0||r==p&&p==0){
					a += m;
				} else {
					vector<int> s{p, q, r};
					sort(s.begin(), s.end());
					if(s[0]==0) b += m*ans[s[1]];
					else b += m*ans[s[0]];
				}
			}
		}

		ans[i] = pow3[i]/(pow3[i]-a)*(1+b/pow3[i]);
	}
	cout << ans[n] << endl;


	return 0;
}
