#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 100000;
int N;
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<ll> step;
	ll cur = 0;;
	step.push_back(0);
	for(int i=0; i<N; i++){
		if(A[i] > cur){
			step.push_back(A[i]);
			cur = A[i];
		}
	}

	vector<vector<int> > stepidx(step.size(), vector<int>());
	for(int i=0; i<N; i++){
		vector<ll>::iterator k = lower_bound(step.begin(), step.end(), A[i]);
		stepidx[k-step.begin()].push_back(i);
	}

	/*
	for(int i=0; i<stepidx.size(); i++){
		cout << step[i] << " ";
		for(int j=0; j<stepidx[i].size(); j++){
			cout << stepidx[i][j] << " ";
		}
		cout << endl;
	}
	*/

	int cnt=0;
	vector<ll> ans(N);
	for(int i=stepidx.size()-1; i>=0; i--){
		for(int j=0; j<stepidx[i].size(); j++){
			ans[stepidx[i][0]] += A[stepidx[i][j]] - A[stepidx[i][0]];
			cnt += 1;
		}
		if(i>0){
			ans[stepidx[i][0]] += cnt * (step[i] - step[i-1]);
		}
	}

	for(int i=0; i<N; i++){
		cout << ans[i] << endl;
	}

	return 0;
}
