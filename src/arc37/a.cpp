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
const int Nmax=25;
int M[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> M[i];

	int ans = 0;
	for(int i=0; i<N; i++) ans += max(0, 80-M[i]);
	cout << ans << endl;

	return 0;
}
