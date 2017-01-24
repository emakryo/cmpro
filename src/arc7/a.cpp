#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
char X;
string S;

int main(){
	cin >> X;
	getline(cin, S);
	getline(cin, S);
	for(int i=0; i<S.size(); i++){
		if(S[i] == X) continue;
		cout << S[i];
	}
	cout << endl;
	return 0;
}
