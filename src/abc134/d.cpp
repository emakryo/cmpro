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
const int Nmax = 2e5;
int N, A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<vector<int> > factors(N+1);
	for(int i=1; i<=N; i++){
		for(int j=2*i; j<=N; j+=i) factors[j].push_back(i);
	}

	vector<int> ans;
	vector<int> count(N+1);
	for(int i=N-1; i>=0; i--){
		if(A[i]!=count[i+1]%2){
			ans.push_back(i+1);
			for(int j: factors[i+1]) count[j]++;
		}
	}

	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for(int i=0; i<ans.size(); i++) cout << ans[i] << (i==ans.size()-1?'\n':' ');

	return 0;
}
