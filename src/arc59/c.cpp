#include<iostream>
#include<vector>
using namespace std;
const int Nmax = 101;
int A[Nmax], N;

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	int ans = 1e9;
	for(int m=-100; m<= 100; m++){
		int cost = 0;
		for(int i=0; i<N; i++) cost+=(m-A[i])*(m-A[i]);
		ans = cost < ans ? cost : ans;
	}

	cout << ans << endl;
	return 0;
}
