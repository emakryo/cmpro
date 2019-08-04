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
const int Nmax = 500;
int N, A[Nmax];
ll K;

vector<int> get_divisors(int x){
	vector<int> div(1, 1);
	for(int i=2; i*i<=x; i++){
		if(x%i==0) div.push_back(i);
	}
	vector<int> ret;
	for(int d: div){
		ret.push_back(d);
		if(d!=x/d) ret.push_back(x/d);
	}
	sort(ret.begin(), ret.end());
	return ret;
}

int main(){
	cin >> N >> K;
	for(int i=0; i<N; i++) cin >> A[i];

	ll sum = 0;
	for(int i=0; i<N; i++) sum += A[i];

	auto divisors = get_divisors(sum);
	int ans = 1;
	//cout << ub << endl;
	for(int div: divisors){
		vector<int> costs;
		int cost_sum = 0;
		//cout << div <<":"<< endl;
		for(int i=0; i<N; i++){
			int p = A[i]/div;
			//cout << A[i]-p*div << endl;
			costs.push_back(A[i]-p*div);
			cost_sum += A[i]-p*div;
		}
		if(cost_sum==0) {
			ans = div;
		}
		sort(costs.begin(), costs.end());
		int cum = 0;
		for(int i=0; i<N; i++){
			cum += costs[i];
			if(cost_sum==(N-i-1)*div){
				break;
			}
		}
		if(cum <= K) ans = div;
	}

	cout << ans << endl;

	return 0;
}
