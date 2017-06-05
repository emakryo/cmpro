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
const int HWmax = 100;
int H,W,C[HWmax+1][HWmax+1];

int main(){
	cin >> H >> W;
	for(int i=1; i<=H; i++){
		for(int j=1; j<=W; j++){
			cin >> C[i][j];
		}
	}

	vector<vector<int> > cum0(H+1, vector<int>(W+1));
	vector<vector<int> > cum1(H+1, vector<int>(W+1));
	for(int i=1; i<=H; i++){
		for(int j=1; j<=W; j++){
			if((i+j)%2==0){
				cum0[i][j] = cum0[i-1][j]+cum0[i][j-1]-cum0[i-1][j-1]+C[i][j];
				cum1[i][j] = cum1[i-1][j]+cum1[i][j-1]-cum1[i-1][j-1];
			}else{
				cum0[i][j] = cum0[i-1][j]+cum0[i][j-1]-cum0[i-1][j-1];
				cum1[i][j] = cum1[i-1][j]+cum1[i][j-1]-cum1[i-1][j-1]+C[i][j];
			}
		}
	}

	int ans=0;
	for(int xt=1; xt<=H; xt++){
		for(int yt=1; yt<=W; yt++){
			for(int xs=0; xs<xt; xs++){
				for(int ys=0; ys<yt; ys++){
					int s0 = cum0[xt][yt]-cum0[xt][ys]-cum0[xs][yt]+cum0[xs][ys];
					int s1 = cum1[xt][yt]-cum1[xt][ys]-cum1[xs][yt]+cum1[xs][ys];
					if(s0 == s1){
						ans = max(ans, (xt-xs)*(yt-ys));
					}
				}
			}
		}
	}

	cout << ans << endl;


	return 0;
}
