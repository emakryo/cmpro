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
const int Nmax = 1000000;
int N;
ll C, K, T[Nmax];

int main(){
	cin >> N >> C >> K;
	for(int i=0; i<N; i++) cin >> T[i];
	sort(T, T+N);

	int ans = 1;
	ll last = T[0];
	ll count = 1;
	for(int i=1; i<N; i++){
		if(T[i] > last+K || count==C){
			ans++;
			last = T[i];
			count = 1;
		}
		else{
			count++;
		}
	}
	
	cout << ans << endl;

	return 0;
}
