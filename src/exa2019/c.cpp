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
const int Qmax = 2e5;
int N, Q;
string S;
char T[Qmax], D[Qmax];

int main(){
	cin >> N >> Q;
	cin >> S;
	for(int i=0; i<Q; i++) cin >> T[i] >> D[i];

	int l=0, r=N-1;
	for(int i=Q-1; i>=0; i--){
		if(S[l]==T[i]&&D[i]=='L') l++;
		if(l>0&&S[l-1]==T[i]&&D[i]=='R') l--;
		if(S[r]==T[i]&&D[i]=='R') r--;
		if(r<N-1&&S[r+1]==T[i]&&D[i]=='L') r++;
	}

	// cout << r-l+1 << " " << l << " " << r << endl;
	cout << r-l+1 << endl;

	return 0;
}
