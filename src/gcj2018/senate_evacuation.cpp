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
const int Nmax = 30;

void solve(){
	int N;
	cin >> N;
	priority_queue<pair<int, char> > que;
	for(int i=0; i<N; i++){
		int p;
		cin >> p;
		if(p>1) que.push(make_pair(p-1, 'A'+i));
	}

	while(!que.empty()){
		for(int i=0; i<2; i++){
			if(que.empty()) break;
			pair<int, char> p = que.top();
			cout << p.second;
			que.pop();
			p.first--;
			if(p.first>0) que.push(p);
		}
		cout << ' ';
	}
	if(N%2==1) cout << (char)('A'+(--N)) << ' ';
	for(char i=0; i<N/2; i++) cout << (char)('A'+2*i) << (char)('A'+2*i+1) << ' ';
	cout << endl;
}

int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		cout << "Case #" << i+1 << ": ";
		solve();
	}

	return 0;
}
