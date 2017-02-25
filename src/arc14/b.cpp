#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
int N;
string W[100];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> W[i];

	int finish = -1;
	for(int i=0; i<N; i++){
		if(i > 0 && W[i][0] != W[i-1][W[i-1].size()-1]){
			finish = i;
			break;
		}
		for(int j=0; j<i; j++){
			if(W[i] == W[j]){
				finish = i;
				break;
			}
		}
		if(finish >= 0) break;
	}

	if(finish < 0) cout << "DRAW" << endl;
	else if(finish%2 == 0) cout << "LOSE" << endl;
	else cout << "WIN" << endl;

	return 0;
}
