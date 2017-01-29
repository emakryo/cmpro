#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	int N, M;
	cin >> N >> M;
	int x,y,z;
	z = (M-2*N)/2;
	if(M-2*N < 0 || z < M-3*N){
		cout << "-1 -1 -1" << endl;
		return 0;
	}

	cout << 3*N-M+z << " " << M-2*N-2*z << " " << z << endl;

	return 0;
}
