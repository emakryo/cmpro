#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<deque>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax = 1e5;
int N;
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	deque<ll> deq;
	deq.push_back(A[0]);

	for(int i=1; i<N; i++){
		auto lb = lower_bound(deq.begin(), deq.end(), A[i]);
		if(lb==deq.begin()){
			deq.push_front(A[i]);
		} else {
			lb--;
			*lb = A[i];
			if(lb+1 != deq.end() && *lb > *(lb+1)) swap(*lb, *(lb+1));
		}
		//cout << i << " ";
		//for(ll x: deq) cout << x << " ";
		//cout << endl;
	}

	cout << deq.size() << endl;

	return 0;
}
