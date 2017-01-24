#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int Nmax = 1e5;
int N;
long T, A[Nmax];
long maxA[Nmax];

int main(){
	cin >> N >> T;

	for(int i=0; i<N; i++) cin >> A[i];

	maxA[N-1] = A[N-1];
	for(int i=N-2; i>=0; i--){
		maxA[i] = max(maxA[i+1], A[i]);
	}

	long interest = 0;
	for(int i=0; i<N; i++){
		interest = max(interest, maxA[i]-A[i]);
	}

	int ans = 0;
	for(int i=0; i<N; i++){
		if(interest == maxA[i]-A[i]) ans++;
	}

	cout << ans << endl;
	return 0;
}
