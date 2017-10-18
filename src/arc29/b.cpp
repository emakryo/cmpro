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
const int Nmax = 5000;
ll A, B, C[Nmax], D[Nmax], N;

int main(){
	cin >> A >> B >> N;
	if(A > B) swap(A, B);
	for(int i=0; i<N; i++){
		cin >> C[i] >> D[i];
		if(C[i] > D[i]) swap(C[i], D[i]);
	}

	for(int i=0; i<N; i++){
		double sx, tx;
		if(A*A+B*B <= C[i]*C[i]){
			sx = M_PI/4;
			tx = M_PI/4;
		}
		else{
			if(A <= C[i]){
				double ub=M_PI/2-atan((double)A/B), lb=0;
				for(int j=0; j<100; j++){
					double mid = (lb+ub)/2;
					if(A*cos(mid)+B*sin(mid) <= C[i]) lb = mid;
					else ub = mid;
				}
				sx = lb;
			}
			else{
				sx = -1;
			}

			if(B <= C[i]){
				double lb=M_PI/2-atan((double)A/B), ub=M_PI/2;
				for(int j=0; j<100; j++){
					double mid = (lb+ub)/2;
					if(A*cos(mid)+B*sin(mid) <= C[i]) ub = mid;
					else lb = mid;
				}
				tx = ub;
			}
			else{
				tx = M_PI/2+1;
			}
		}

		double sy, ty;
		if(A*A+B*B < D[i]*D[i]){
			sy = M_PI/4;
			ty = M_PI/4;
		}
		else{
			if(B <= D[i]){
				double ub=M_PI/2-atan((double)B/A), lb=0;
				for(int j=0; j<100; j++){
					double mid = (lb+ub)/2;
					if(A*sin(mid)+B*cos(mid) <= D[i]) lb = mid;
					else ub = mid;
				}
				sy = lb;
			}
			else{
				sy = -1;
			}

			if(A <= D[i]){
				double lb=M_PI/2-atan((double)B/A), ub=M_PI/2;
				for(int j=0; j<100; j++){
					double mid = (lb+ub)/2;
					if(A*sin(mid)+B*cos(mid) <= D[i]) ub = mid;
					else lb = mid;
				}
				ty = ub;
			}
			else{
				ty = M_PI/2+1;
			}
		}

		//cout << sx << " " << tx << " " << sy << " " << ty << endl;
		if(0 < min(sx, sy) || max(tx, ty) < M_PI/2 || tx < sy || ty < sx){
			cout << "YES" << endl;
		}
		else{
			cout << "NO" << endl;
		}

	}

	return 0;
}
