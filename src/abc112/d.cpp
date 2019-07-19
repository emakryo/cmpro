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

int main(){
	int N, M;
	cin >> N >> M;

	vector<int> divs;
	for(int i=1; i*i<=M; i++){
		if(M%i==0){
			divs.push_back(i);
			if(M/i!=i) divs.push_back(M/i);
		}
	}

	sort(divs.begin(), divs.end());

	int lb = *lower_bound(divs.begin(), divs.end(), N);
	cout << M/lb << endl;

	return 0;
}
