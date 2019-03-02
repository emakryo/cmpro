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

int main(){
	int N;
	cin >> N;
	double sum=0;
	for(int i=0; i<N; i++){
		double x;
		string u;
		cin >> x >> u;
		sum += (u=="JPY"?x:380000*x);
	}

	cout << setprecision(10) << sum << endl;

	return 0;
}
