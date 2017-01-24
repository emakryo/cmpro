#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 10;
int N;
int A[Nmax], B[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i] >> B[i];

	int sum =0;
	for(int i=0; i<N; i++) sum += A[i]*B[i];
	cout << (int)(sum*1.05) << endl;
	return 0;
}
