#include<iostream>
#include<map>
#include<vector>
using namespace std;
const int Nmax = 400;
int N, C[4][Nmax];

long encode(int c0,int c1,int c2,int c3){
	long base=1000;
	long x = c3+base*c2+base*base*c1+base*base*base*c0;
	long m = x;
	for(int i=0; i<3; i++){
		x = x/base+(x%base)*base*base*base;
		m = min(m, x);
	}
	return m;
}

int rot(long code){
	int c[4];
	int base = 1000;
	for(int i=0; i<4; i++) {
		c[i] = code%base;
		code /= base;
	}
	if(c[0]==c[1]&&c[1]==c[2]&&c[2]==c[3]) return 4;
	if(c[0]==c[2]&&c[1]==c[3]) return 2;
	return 1;
}

int main(){
	cin >> N;
	for(int i=0; i<N; i++){
		for(int j=0; j<4; j++){
			cin >> C[j][i];
		}
	}

	map<long, vector<int> > e2f;
	for(int i=0; i<N; i++){
		long x = encode(C[0][i],C[1][i],C[2][i],C[3][i]);
		e2f[x].push_back(i);
	}

	long ans = 0;

	for(int i=0; i<N; i++){
		for(int j=i+1; j<N; j++){
			for(int k=0; k<4; k++){
				long f[4];
				f[0] = encode(C[1][i],C[0][i],C[(k+0)%4][j],C[(k+3)%4][j]);
				f[1] = encode(C[2][i],C[1][i],C[(k+3)%4][j],C[(k+2)%4][j]);
				f[2] = encode(C[3][i],C[2][i],C[(k+2)%4][j],C[(k+1)%4][j]);
				f[3] = encode(C[0][i],C[3][i],C[(k+1)%4][j],C[(k+0)%4][j]);
				if(e2f.find(f[0]) == e2f.end() ||
					e2f.find(f[1]) == e2f.end() ||
					e2f.find(f[2]) == e2f.end() ||
					e2f.find(f[3]) == e2f.end()) continue;
				/*
				cout << i << " " << j << endl;
				cout << f[0] << endl;
				cout << f[1] << endl;
				cout << f[2] << endl;
				cout << f[3] << endl;
				*/
				long c[4];
				long a=0;
				for(int m=0; m<4; m++){
					c[m]=0;
					for(auto l=e2f[f[m]].begin(); l!=e2f[f[m]].end(); l++){
						//cout << " " << *l << endl;
						if(*l<=i || *l==j) continue;
						c[m]++;
					}
					//cout << c[m] << " ";
				}
				if(f[0]==f[1]&&f[1]==f[2]&&f[2]==f[3]){
					if(c[0]>=4){
						a = c[0]*(c[0]-1)*(c[0]-2)*(c[0]-3);
					}
				}
				else if(f[0]==f[1]&&f[1]==f[2]){
					if(c[0]>=3){
						a = c[0]*(c[0]-1)*(c[0]-2)*c[3];
					}
				}
				else if(f[0]==f[1]&&f[1]==f[3]){
					if(c[0]>=3){
						a = c[0]*(c[0]-1)*(c[0]-2)*c[2];
					}
				}
				else if(f[0]==f[2]&&f[2]==f[3]){
					if(c[0]>=3){
						a = c[0]*(c[0]-1)*(c[0]-2)*c[1];
					}
				}
				else if(f[1]==f[2]&&f[2]==f[3]){
					if(c[1]>=3){
						a = c[1]*(c[1]-1)*(c[1]-2)*c[0];
					}
				}
				else if(f[0]==f[2]&&f[1]==f[3]){
					if(c[0]>=2&&c[1]>=2){
						a = c[0]*(c[0]-1)*c[1]*(c[1]-1);
					}
				}
				else if(f[0]==f[1]&&f[2]==f[3]){
					if(c[0]>=2&&c[2]>=2){
						a = c[0]*(c[0]-1)*c[2]*(c[2]-1);
					}
				}
				else if(f[0]==f[3]&&f[1]==f[2]){
					if(c[0]>=2&&c[1]>=2){
						a = c[0]*(c[0]-1)*c[1]*(c[1]-1);
					}
				}
				else if(f[0]==f[2]){
					if(c[0]>=2){
						a = c[0]*(c[0]-1)*c[1]*c[3];
					}
				}
				else if(f[1]==f[3]){
					if(c[1]>=2){
						a = c[1]*(c[1]-1)*c[0]*c[2];
					}
				}
				else if(f[0]==f[1]){
					if(c[0]>=2){
						a = c[0]*(c[0]-1)*c[2]*c[3];
					}
				}
				else if(f[1]==f[2]){
					if(c[1]>=2){
						a = c[1]*(c[1]-1)*c[0]*c[3];
					}
				}
				else if(f[2]==f[3]){
					if(c[2]>=2){
						a = c[2]*(c[2]-1)*c[0]*c[1];
					}
				}
				else if(f[0]==f[3]){
					if(c[0]>=2){
						a = c[0]*(c[0]-1)*c[1]*c[2];
					}
				}
				else {
					a = c[0]*c[1]*c[2]*c[3];
				}
				for(int m=0; m<4; m++) a*=rot(f[m]);
				//cout << a << endl;
				ans += a;
			}
		}
	}

	cout << ans << endl;

	return 0;
}
