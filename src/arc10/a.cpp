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
int N,M,C[Mmax],A,B;

int main(){
	cin >> N >> M >> A >> B;
	for(int i=0; i<M; i++) cin >> C[i];

	int x = N;
	for(int i=0; i<M; i++){
		if(x <= A) x += B;
		x -= C[i];
		if(x < 0){
			cout << i+1 << endl;
			return 0;
		}
	}

	cout << "complete" << endl;

	return 0;
}
