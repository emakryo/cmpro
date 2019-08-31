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
const int Nmax = 200000;
int N, A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];
	vector<int> x(A, A+N);
	sort(x.begin(), x.end());

	for(int i=0; i<N; i++){
		if(A[i]==x[N-1]) cout << x[N-2] << endl;
		else cout << x[N-1] << endl;
	}

	return 0;
}
