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

int main(){
	int N;
	string S;
	cin >> N;
	cin >> S;

	int ans = 1e8;
	for(int i=0; i<N-3; i++){
		int x = 0;
		x += min(('A'+26-S[i])%26, (S[i]+26-'A')%26);
		x += min(('C'+26-S[i+1])%26, (S[i+1]+26-'C')%26);
		x += min(('T'+26-S[i+2])%26, (S[i+2]+26-'T')%26);
		x += min(('G'+26-S[i+3])%26, (S[i+3]+26-'G')%26);
		ans = min(ans, x);
	}

	cout << ans << endl;

	return 0;
}
