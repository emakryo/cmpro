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
int A, B, C, S;

int main(){
	cin >> A >> B >> C >> S;

	if(S-3 <= A+B+C && A+B+C <= S){
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}

	return 0;
}
