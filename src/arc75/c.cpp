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
const int Nmax = 100;
int N, S[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> S[i];
	}

	sort(S, S+N);
	int ans = 0;
	for(int i=0; i<N; i++) ans += S[i];

	if(ans % 10 == 0){
		int i=0;
		while(i<N && S[i]%10 == 0) i++;
		if(i < N) ans -= S[i];
		else ans = 0;
	}

	cout << ans << endl;

	return 0;
}
