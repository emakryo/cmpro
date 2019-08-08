#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string S;
int X, Y;

int main(){
	cin >> S;
	cin >> X >> Y;

	int nf=0;
	vector<int> nx, ny;
	for(int i=0; i<S.size(); i++){
		if(S[i]=='F') nf++;
		else{
			if(nx.size()==ny.size()) nx.push_back(nf);
			else ny.push_back(nf);
			nf=0;
		}
	}
	if(nx.size()==ny.size()) nx.push_back(nf);
	else ny.push_back(nf);

	X-=nx[0];

	//cout << nx[0] << endl;

	vector<bool> x(10000), y(10000);
	int x_sum=0, y_sum=0;
	x[0] = y[0] = true;
	for(int i=1; i<nx.size(); i++){
		x_sum += nx[i];
		//cout << nx[i] << endl;
		for(int j=0; j<x.size(); j++){
			if(j+nx[i]<x.size()) x[j+nx[i]] = x[j+nx[i]] || x[j];
		}
	}

	//cout << endl;
	for(int i=0; i<ny.size(); i++){
		y_sum += ny[i];
		//cout << ny[i] << endl;
		for(int j=0; j<y.size(); j++){
			if(j+ny[i]<y.size()) y[j+ny[i]] = y[j+ny[i]] || y[j];
		}
	}

	int px = (X+x_sum)/2;
	int py = (Y+y_sum)/2;
	//cout << px << " " << py << endl;
	if((X+x_sum)%2==0&&0<=px&&px<=x_sum&&x[px]&&
			(Y+y_sum)%2==0&&0<=py&&py<=y_sum&&y[py]) cout << "Yes" << endl;
	else cout << "No" << endl;

	return 0;
}
