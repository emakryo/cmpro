#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
int N, A, B, L;

int main(){
	cin >> N >> A >> B >> L;
	double dist = L;
	for(int i=0; i<N; i++){
		dist = dist*B/A;
	}

	cout << fixed << setprecision(10) << dist << endl;

	return 0;
}
