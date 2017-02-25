#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
int N;
string S;

int main(){
	cin >> N;
	cin >> S;

	int r,g,b;
	r = g = b = 0;
	for(int i=0; i<N; i++){
		if(S[i] == 'R') r++;
		if(S[i] == 'G') g++;
		if(S[i] == 'B') b++;
	}

	cout << r%2+g%2+b%2 << endl;

	return 0;
}
