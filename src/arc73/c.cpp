#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Nmax = 2e5;
int N;
ll T, X[Nmax];

int main(){
	cin >> N >> T;
	for(int i=0; i<N; i++) cin >> X[i];

	ll sum = 0;
	for(int i=1; i<N; i++){
		sum += min(T, X[i]-X[i-1]);
	}
	sum += T;

	cout << sum << endl;

	return 0;
}
