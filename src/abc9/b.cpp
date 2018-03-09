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
int N, A[100];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];
	sort(A, A+N);
	int a = N-2;
	while(A[a] == A[N-1]) a--;
	cout << A[a] << endl;

	return 0;
}
