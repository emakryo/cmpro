#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	int E[6], B, L[6];
	for(int i=0; i<6; i++) cin >> E[i];
	cin >> B;
	for(int i=0; i<6; i++) cin >> L[i];

	int match=0, bonus=0;
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			match += E[i] == L[j] ? 1 : 0;
			bonus += B == L[j] ? 1 : 0;
		}
	}

	if(match == 6) cout << 1 << endl;
	else if(match == 5 && bonus > 0) cout << 2 << endl;
	else if(match == 5) cout << 3 << endl;
	else if(match == 4) cout << 4 << endl;
	else if(match == 3) cout << 5 << endl;
	else cout << 0 << endl;

	return 0;
}
