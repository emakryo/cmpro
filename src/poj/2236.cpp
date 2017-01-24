#include<iostream>
#include<algorithm>
#include<sstream>
using namespace std;
int N, D;
const int Nmax = 1001;
int X[Nmax], Y[Nmax];
int par[Nmax];

int find(int n){
	if(n < 0 || par[n] < 0) return -1;
	if(par[n] == n) return n;
	else return par[n] = find(par[n]);
}

void print(){
	for(int i=0; i<N; i++) cout << par[i] << " ";
	cout << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin >> N >> D;
	for(int i=0; i<N; i++){
		cin >> X[i] >> Y[i];
		par[i] = -1;
	}

	char line[100];
	while(cin.getline(line, 99)){
		stringstream strm(line);
		char op[10];
		strm >> op;
		if(op[0] == 'O'){
			int p;
			strm >> p;
			if(par[p-1] >= 0) continue;
			par[p-1] = p-1;
			//cout << p << endl;
			for(int i=0; i<N; i++){
				if((X[i]-X[p-1])*(X[i]-X[p-1])+(Y[i]-Y[p-1])*(Y[i]-Y[p-1]) <= D*D &&
						par[i] >= 0){
					par[find(i)] = p-1;
				}
			}
			//print();
		}
		else if(op[0] == 'S'){
			int p,q;
			strm >> p >> q;
			//cout << p << " " << q << endl;
			if(find(p-1) == find(q-1) && find(p-1) >= 0){
				cout << "SUCCESS" << endl;
			}
			else{
				cout << "FAIL" << endl;
			}
		}
	}

	return 0;
}
