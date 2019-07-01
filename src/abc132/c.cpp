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
const int Nmax = 1e5;
int D[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> D[i];

	sort(D, D+N);

	cout << D[N/2]-D[N/2-1] << endl;

	return 0;
}
