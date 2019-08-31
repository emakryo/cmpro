#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
const int Nmax = 1000;
int X[Nmax], Y[Nmax], C[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i] >> C[i];

	double lb=0, ub=1e20;
	for(int i=0; i<100; i++){
		double med = (lb+ub)/2;
		double x_min = X[0]-med/C[0];
		double x_max = X[0]+med/C[0];
		double y_min = Y[0]-med/C[0];
		double y_max = Y[0]+med/C[0];

		for(int i=1; i<N; i++){
			x_min = max(x_min, X[i]-med/C[i]);
			x_max = min(x_max, X[i]+med/C[i]);
			y_min = max(y_min, Y[i]-med/C[i]);
			y_max = min(y_max, Y[i]+med/C[i]);
		}
		//cout << x_min << " " << x_max << " " << y_min << " " << y_max << endl;
		//cout << med << endl;
		if(x_min<=x_max&&y_min<=y_max) ub = med;
		else lb = med;
	}

	cout << fixed << setprecision(10) << ub << endl;


	return 0;
}
