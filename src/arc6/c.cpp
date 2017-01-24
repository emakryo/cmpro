#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 50;
int N, W[Nmax];

bool possible(int n){
	vector<int> bin(n, 1e7);
	for(int i=0; i<N; i++){
		int idx = -1;
		int max_w = 0;
		for(int j=0; j<n; j++){
			if(bin[j] >= W[i] && W[i] >= max_w){
				idx = j;
				max_w = W[i];
			}
		}

		if(idx < 0) return false;

		bin[idx] = W[i];
	}

	return true;
}


int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> W[i];

	int lower = 0, upper = 50;
	while(upper - lower > 1) {
		int center = (lower+upper)/2;
		if(possible(center)){
			upper = center;
		}
		else{
			lower = center;
		}
	}

	cout << upper << endl;
	return 0;
}
