#include<iostream>
#include<vector>
using namespace std;
const int Nmax = 10000;
int N,T[Nmax],A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> T[i] >> A[i];
	}

	long t=T[0],a=A[0];
	for(int i=1; i<N; i++){
		long kt = t%T[i]>0 ? t/T[i]+1 : t/T[i];
		long ka = a%A[i]>0 ? a/A[i]+1 : a/A[i];
		long k = max(kt,ka);
		t = k*T[i];
		a = k*A[i];
	}

	cout << t+a << endl;
	return 0;
}
