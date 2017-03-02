#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 32;
int N;
ll X, W[Nmax];

int main(){
	cin >> N >> X;
	for(int i=0; i<N; i++) cin >> W[i];

	if(N==1){
		cout << (W[0]==X ? 1 : 0) << endl;
		return 0;
	}

	vector<ll> sum1;
	sum1.push_back(0);
	sum1.push_back(W[0]);
	for(int i=1; i<N/2; i++){
		int s=sum1.size();
		for(int j=0; j<s; j++){
			sum1.push_back(sum1[j]+W[i]);
		}
	}

	vector<ll> sum2;
	sum2.push_back(0);
	sum2.push_back(W[N/2]);
	for(int i=N/2+1; i<N; i++){
		int s=sum2.size();
		for(int j=0; j<s; j++){
			sum2.push_back(sum2[j]+W[i]);
		}
	}

	sort(sum2.begin(), sum2.end());

	ll ans = 0;
	for(int i=0; i<sum1.size(); i++){
		ans += upper_bound(sum2.begin(), sum2.end(), X-sum1[i]) -
			lower_bound(sum2.begin(), sum2.end(), X-sum1[i]);
	}

	cout << ans << endl;


	return 0;
}
