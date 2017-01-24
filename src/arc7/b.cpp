#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Mmax = 100;
int N, M, D[Mmax];
int vec[Mmax+1];

bool cmp(int x, int y){
	return vec[x] < vec[y];
}

int main(){
	cin >> N >> M;
	for(int i=0; i<M; i++) cin >> D[i];
	for(int i=0; i<N+1; i++) vec[i] = i;

	int k = 0;
	for(int i=0; i<M; i++) {
		swap(vec[k], vec[D[i]]);
		k = D[i];
		//cout << k << endl;
	}

	/*
	for(int i=0; i<N; i++) cout << vec[i] << " ";
	cout << endl;
	*/

	vector<int> vec2(N+1);
	for(int i=0; i<N+1; i++) vec2[i] = i;
	sort(vec2.begin(), vec2.end(), cmp);
	for(int i=0; i<N; i++) cout << vec2[i+1] << endl;

	return 0;
}
