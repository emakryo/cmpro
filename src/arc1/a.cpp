#include<iostream>
#include<algorithm>
using namespace std;
const int INF = 1e7;
int N;
string C;
int cnt[4];

int main(){
	cin >> N >> C;

	for(int i=0; i<N; i++){
		cnt[C[i]-'1']++;
	}

	int smax=0;
	int smin=INF;

	for(int i=0; i<4; i++){
		smax = max(smax, cnt[i]);
		smin = min(smin, cnt[i]);
	}

	cout << smax << " " << smin << endl;

	return 0;
}
