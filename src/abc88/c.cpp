#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int C[3][3];

int main(){
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			cin >> C[i][j];
		}
	}

	for(int i=0; i<3; i++){
		bool ok = true;
		for(int j=0; j<3; j++){
			ok = ok && (C[i][j]-C[i][(j+1)%3])==(C[(i+1)%3][j]-C[(i+1)%3][(j+1)%3]);
			ok = ok && (C[i][j]-C[(i+1)%3][j])==(C[i][(j+1)%3]-C[(i+1)%3][(j+1)%3]);
		}
		if(!ok){
			cout << "No" << endl;
			return 0;
		}
	}
	cout << "Yes" << endl;

	return 0;
}
