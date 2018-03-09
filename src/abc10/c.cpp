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
int N;
double Ax, Ay, Bx, By, T, V;
double X[1000], Y[1000];

int main(){
	cin >> Ax >> Ay >> Bx >> By >> T >> V;
	cin >> N;
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i];

	for(int i=0; i<N; i++){
		double d = sqrt((Ax-X[i])*(Ax-X[i])+(Ay-Y[i])*(Ay-Y[i]))
			+ sqrt((Bx-X[i])*(Bx-X[i])+(By-Y[i])*(By-Y[i]));
		if(d < V*T+1e-8){
			cout << "YES" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;

	return 0;
}
