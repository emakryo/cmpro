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
const int Hmax = 500;
int H, W;
int A[Hmax][Hmax];

int main(){
	cin >> H >> W;
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			cin >> A[i][j];
		}
	}

	vector<pair<pair<int, int>, pair<int, int> > > ans;
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(A[i][j]%2==0) continue;
			if(j+1<W){
				ans.push_back(make_pair(
							make_pair(i, j),
							make_pair(i, j+1)));
				A[i][j]--; A[i][j+1]++;
			} else if(i+1<H){
				ans.push_back(make_pair(
							make_pair(i, j),
							make_pair(i+1, j)));
				A[i][j]--; A[i+1][j]++;
			}
		}
	}

	cout << ans.size() << endl;
	for(auto p: ans){
		cout << p.first.first+1 << " " << p.first.second+1 << " ";
		cout << p.second.first+1 << " " << p.second.second+1 << endl;
	}

	return 0;
}
