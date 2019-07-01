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
int N;
int P[20];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> P[i];

	int ans=0;
	for(int i=1; i<N-1; i++){
		if((P[i-1]<P[i]&&P[i]<P[i+1])||(P[i+1]<P[i]&&P[i]<P[i-1])){
			ans++;
		}
	}

	cout << ans << endl;

	return 0;
}
