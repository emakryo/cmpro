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
const int Nmax = 1e5;
int N;
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<int> c(4);
	for(int i=0; i<N; i++) c[A[i]%4] += 1;

	if((c[2]==0 && c[1]+c[3] <= c[0]+1) ||
			(c[1]+c[3] <= c[0]))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	return 0;
}
