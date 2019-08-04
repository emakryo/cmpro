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
const int Nmax = 50;
int N, P[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> P[i];

	vector<pair<int, int>> pi;
	for(int i=0; i<N; i++) pi.push_back({P[i], i});

	sort(pi.begin(), pi.end());
	int n = 0;
	for(int i=0; i<N; i++){
		if(pi[i].second!=i) n++;
	}

	if(n<=2) cout << "YES" << endl;
	else cout << "NO" << endl;

	return 0;
}
