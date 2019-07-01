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
int N, K;
const int Nmax=1e5;
string S;

int main(){
	cin >> N >> K;
	cin >> S;

	vector<int> x;
	if(S[0]=='0') x.push_back(0);
	int n = 1;
	for(int i=1; i<N; i++){
		if(S[i]!=S[i-1]){
			x.push_back(n);
			n = 1;
		} else {
			n += 1;
		}
	}
	x.push_back(n);

	//for(int i=0; i<x.size(); i++) cout << x[i] << endl;
	int sum = 0;
	//cout << N << " " << 2*K+1 << endl;
	for(int i=0; i<min((int)x.size(), 2*K+1); i++){
		sum += x[i];
	}
	//cout << sum << endl;

	int ans = sum;
	for(int i=0; i+2*K+1<x.size(); i+=2){
		sum -= x[i]+x[i+1];
		sum += x[i+2*K+1];
		if(i+2*K+2<x.size()) sum += x[i+2*K+2];
		ans = max(ans, sum);
	}
	cout << ans << endl;

	return 0;
}
