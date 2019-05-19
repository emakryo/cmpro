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
const int Pmax = 1e5;
int P, Q;
int X[Pmax], Y[Pmax];
char D[Pmax];
int d[] = {1, -1};

pair<int, int> solve(){
	cin >> P >> Q;
	string s;
	for(int i=0; i<P; i++){
		cin >> X[i] >> Y[i] >> s;
		D[i] = s[0];
	}

	pair<int, int> ans;
	vector<int> xs(1, 0), ys(1, 0);
	for(int j=0; j<P; j++){
		for(int k=0; k<2; k++){
			int x=X[j]+d[k];
			int y=Y[j]+d[k];
			if(0<=x && x<=Q) xs.push_back(x);
			if(0<=y && y<=Q) ys.push_back(y);
		}
	}
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());

	int nx_max = 0;
	for(int x: xs){
		int n=0;
		for(int i=0; i<P; i++){
			if(D[i]=='E'&&x>X[i]) n++;
			if(D[i]=='W'&&x<X[i]) n++;
		}
		if(n > nx_max){
			ans.first = x;
			nx_max = n;
		}
	}
	int ny_max = 0;
	for(int y: ys){
		int n=0;
		for(int i=0; i<P; i++){
			if(D[i]=='N'&&y>Y[i]) n++;
			if(D[i]=='S'&&y<Y[i]) n++;
		}
		if(n > ny_max){
			ans.second = y;
			ny_max = n;
		}
	}

	return ans;
}


int main(){
	int t;
	cin >> t;
	for(int i=0; i<t; i++){
		pair<int, int> ans = solve();
		cout << "Case #" << i+1 << ": " << ans.first << " " << ans.second << endl;
	}

	return 0;
}
