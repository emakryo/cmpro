#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax=30000;
int N, C[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> C[i];
		C[i]--;
	}

	vector<int> dp;
	for(int i=0; i<N; i++){
		vector<int>::iterator l = lower_bound(dp.begin(), dp.end(), C[i]);
		if(l == dp.end()){
			dp.push_back(C[i]);
		}
		else{
			*l = C[i];
		}
	}

	cout << N-dp.size() << endl;

	return 0;
}
