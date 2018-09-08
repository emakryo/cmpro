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
int N, A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<int> vec(Nmax);
	for(int i=0; i<N; i++){
		vec[A[i]] += 1;
	}

	int ans = 0;
	for(int i=1; i<Nmax-1; i++){
		ans = max(ans, vec[i-1]+vec[i]+vec[i+1]);
	}

	cout << ans << endl;
	return 0;
}
