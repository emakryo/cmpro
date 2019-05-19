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

int solve(int N, int M){
	vector<vector<int> > buf(7, vector<int>(18));
	for(int i=0; i<7; i++){
		for(int j=0; j<18; j++){
			cout << i+12 << (j==17?'\n':' ');
		}
		cout << flush;
		for(int j=0; j<18; j++){
			cin >> buf[i][j];
			if(buf[i][j] < 0) return -1;
		}
	}

	vector<int> sum(7);
	for(int i=0; i<7; i++){
		for(int j=0; j<18; j++){
			sum[i] += buf[i][j];
		}
	}

	vector<int> count(1000005);
	for(int i=0; i<7; i++){
		int j=0;
		while((i+12)*j+sum[i] <= 1000000){
			count[(i+12)*j+sum[i]] += 1;
			j += 1;
		}
	}
	for(int i=0; i<=1000000; i++){
		if(count[i]==7){
			int verdict;
			cout << i << endl;
			cin >> verdict;
			return verdict;
		}
	}
	return -1;
}

int main(){
	int T, N, M;
	cin >> T >> N >> M;
	for(int i=0; i<T; i++){
		if(solve(N, M) < 0) break;
	}

	return 0;
}
