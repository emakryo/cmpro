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
const int Nmax = 1e5;
const double INF = 1e17;
double X[Nmax], Y[Nmax];
string D[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> X[i] >> Y[i] >> D[i];

	vector<double> ts(1, 0);

	double rmin=INF, rmax=-INF;
	double lmin=INF, lmax=-INF;
	double xmin=INF, xmax=-INF;
	double umin=INF, umax=-INF;
	double dmin=INF, dmax=-INF;
	double ymin=INF, ymax=-INF;
	for(int i=0; i<N; i++){
		if(D[i]=="R"){
			rmin = min(rmin, X[i]);
			rmax = max(rmax, X[i]);
			ymin = min(ymin, Y[i]);
			ymax = max(ymax, Y[i]);
		}
		if(D[i]=="L"){
			lmin = min(lmin, X[i]);
			lmax = max(lmax, X[i]);
			ymin = min(ymin, Y[i]);
			ymax = max(ymax, Y[i]);
		}
		if(D[i]=="U"){
			umin = min(umin, Y[i]);
			umax = max(umax, Y[i]);
			xmin = min(xmin, X[i]);
			xmax = max(xmax, X[i]);
		}
		if(D[i]=="D"){
			dmin = min(dmin, Y[i]);
			dmax = max(dmax, Y[i]);
			xmin = min(xmin, X[i]);
			xmax = max(xmax, X[i]);
		}
	}

	//cout << dmax << " " << umax << endl;

	if(rmax<lmax){
		ts.push_back((lmax-rmax)/2.0);
	}
	if(xmax<lmax){
		ts.push_back(lmax-xmax);
	}
	if(rmax<xmax){
		ts.push_back(xmax-rmax);
	}
	if(rmin<lmin){
		ts.push_back((lmin-rmin)/2.0);
	}
	if(rmin<xmin){
		ts.push_back(xmin-rmin);
	}
	if(xmin<lmin){
		ts.push_back(lmin-xmin);
	}
	if(umax<dmax){
		ts.push_back((dmax-umax)/2.0);
	}
	if(ymax<dmax){
		ts.push_back(dmax-ymax);
	}
	if(umax<ymax){
		ts.push_back(ymax-umax);
	}
	if(umin<dmin){
		ts.push_back((dmin-umin)/2.0);
	}
	if(ymin<dmin){
		ts.push_back(dmin-ymin);
	}
	if(umin<ymin){
		ts.push_back(ymin-umin);
	}

	double ans = INF;
	for(double t: ts){
		if(t<0||t>1e10) continue;
		double xmin=INF, xmax=-INF, ymin=INF, ymax=-INF;
		for(int i=0; i<N; i++){
			if(D[i]=="R"){
				xmin = min(xmin, X[i]+t);
				xmax = max(xmax, X[i]+t);
				ymin = min(ymin, Y[i]);
				ymax = max(ymax, Y[i]);
			}
			if(D[i]=="L"){
				xmin = min(xmin, X[i]-t);
				xmax = max(xmax, X[i]-t);
				ymin = min(ymin, Y[i]);
				ymax = max(ymax, Y[i]);
			}
			if(D[i]=="U"){
				xmin = min(xmin, X[i]);
				xmax = max(xmax, X[i]);
				ymin = min(ymin, Y[i]+t);
				ymax = max(ymax, Y[i]+t);
			}
			if(D[i]=="D"){
				xmin = min(xmin, X[i]);
				xmax = max(xmax, X[i]);
				ymin = min(ymin, Y[i]-t);
				ymax = max(ymax, Y[i]-t);
			}
		}
		//cout << t << " " << xmax << " " << xmin << " " << ymax << " " << ymin << endl;
		ans = min(ans, (xmax-xmin)*(ymax-ymin));
	}

	cout << setprecision(15) << fixed << ans << endl;
	//cout << ans << endl;

	return 0;
}
