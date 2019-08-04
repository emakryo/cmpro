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
const int Nmax = 1e5;
int N;
ll H[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> H[i];

	H[0]--;
	bool lowable=true;
	for(int i=1; i<N; i++){
		if(H[i]>H[i-1]){
			H[i]--;
			lowable=true;
		}
		else if(H[i]==H[i-1]) lowable=false;
		else {
			cout << "No" << endl;
			return 0;
		}
		//cout << i << " " << H[i] << endl;
	}

	cout << "Yes" << endl;

	return 0;
}
