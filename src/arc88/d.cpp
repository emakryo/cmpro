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
string S;

int main(){
	cin >> S;
	int N = S.size();
	vector<int> cum;
	cum.push_back(0);
	for(int i=0; i<N; i++) cum.push_back(S[i]-'0'+cum[i]);

	for(int k=(N+1)/2; k<=N; k++){
		int n = cum[k]-cum[N-k];
		//cout << k << " " << N-k << " " << n << endl;
		if(0<n&&n<2*k-N){
			cout << k-1 << endl;
			return 0;
		}
	}

	cout << N << endl;
	return 0;
}
