#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 1000;
const int Mmax = 100;
int N;
ll X[Nmax],Y[Nmax],Z[Nmax];
int M[Nmax];
ll Xi[Nmax][Mmax];
ll Yi[Nmax][Mmax];
ll Zi[Nmax][Mmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		cin >> X[i] >> Y[i] >> Z[i];
		cin >> M[i];
		for(int j=0; j<M[i]; j++){
			cin >> Xi[i][j] >> Yi[i][j] >> Zi[i][j];
		}
	}

	int a=0, b=0;
	ll ans = 0;
	for(int i=0; i<N; i++){
		ll xmin, ymin, zmin;
		ll xmax, ymax, zmax;
		xmin = xmax = Xi[i][0];
		ymin = ymax = Yi[i][0];
		zmin = zmax = Zi[i][0];
		for(int j=0; j<M[i]; j++){
			xmin = min(xmin, Xi[i][j]);
			xmax = max(xmax, Xi[i][j]);
			ymin = min(ymin, Yi[i][j]);
			ymax = max(ymax, Yi[i][j]);
			zmin = min(zmin, Zi[i][j]);
			zmax = max(zmax, Zi[i][j]);
		}

		ans ^= xmin ^ ymin ^ zmin;
		ans ^= (X[i]-1-xmax) ^ (Y[i]-1-ymax) ^ (Z[i]-1-zmax);
	}

	cout << (ans ? "WIN" : "LOSE") << endl;

	return 0;
}
