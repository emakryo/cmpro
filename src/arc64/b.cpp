#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
string S;

int main(){
	cin >> S;

	if((S.size()%2 == 0) != (S[0] == S[S.size()-1]))
		cout << "Second" << endl;
	else
		cout << "First" << endl;
	return 0;
}
