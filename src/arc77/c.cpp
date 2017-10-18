#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<deque>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
const int Nmax=200000;
int N;
ll A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> A[i];
	}

	deque<ll> deq;
	for(int i=0; i<N; i++){
		if(i%2==1){
			deq.push_back(A[i]);
		}
		else{
			deq.push_front(A[i]);
		}
	}

	if(N%2==0){
		reverse(deq.begin(), deq.end());
	}

	for(int i=0; i<N; i++){
		cout << deq[i] << (i==N-1 ? '\n' : ' ');
	}
	cout << flush;

	return 0;
}
