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
int N, A, B;

int main(){
	cin >> N >> A >> B;
	cout << min(A*N, B) << endl;

	return 0;
}
