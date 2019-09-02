#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int main(){
	int H, W;
	cin >> H >> W;
	vector<string> S(H);
	for(int i=0; i<H; i++) cin >> S[i];

	vector<vector<int>> x(H, vector<int>(W)), y(H, vector<int>(W));

	for(int i=0; i<H; i++){
		int j=0;
		while(j<W){
			while(j<W&&S[i][j]=='#') j++;
			int k=j;
			while(k<W&&S[i][k]=='.') k++;
			int a = k-j;
			while(j<k) x[i][j++] = a;
		}
		debug(x[i]);
	}

	for(int i=0; i<W; i++){
		int j=0;
		while(j<H){
			while(j<H&&S[j][i]=='#') j++;
			int k=j;
			while(k<H&&S[k][i]=='.') k++;
			int a = k-j;
			while(j<k) y[j++][i] = a;
		}
	}

	int ans = 0;
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			ans = max(ans, x[i][j]+y[i][j]-1);
		}
	}
	cout << ans << endl;
	return 0;
}
