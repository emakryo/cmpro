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

int main(){
	int H, W;
	cin >> H >> W;
	vector<string> S(H);
	for(int i=0; i<H; i++) cin >> S[i];

	vector<vector<int>> grundy(H, vector<int>(W));
	grundy[H-1][W-1] = 0;
	for(int i=H-1; i>=0; i--) for(int j=W-1; j>=0; j--){
		vector<int> next;
		if(i<H-1&&S[i+1][j]=='.') next.push_back(grundy[i+1][j]);
		if(j<W-1&&S[i][j+1]=='.') next.push_back(grundy[i][j+1]);
		if(i<H-1&&j<W-1&&S[i+1][j+1]=='.') next.push_back(grundy[i+1][j+1]);
		if(next.size()==0){
			grundy[i][j] = 0;
		} else {
			sort(next.begin(), next.end());
			int g=0;
			int k=0;
			while(next[k]==g){
				g++;
				k++;
			}
			grundy[i][j] = g;
		}
	}
	for(int i=0; i<H; i++) debugv(grundy[i]);
	if(grundy[0][0]==0){
		cout << "Second" << endl;
	} else {
		cout << "First" << endl;
	}

	return 0;
}
