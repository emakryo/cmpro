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
const int Kmax = 100;
ll A[Kmax], C[Kmax], M;
int K;

void matmul(vector<vector<ll> > &a, vector<vector<ll> > &b, vector<vector<ll> > &c){
	for(int i=0; i<K; i++){
		for(int j=0; j<K; j++){
			c[i][j] = 0;
			for(int k=0; k<K; k++){
				c[i][j] = c[i][j] ^ (a[i][k] & b[k][j]);
			}
		}
	}
}

void matpow(vector<vector<ll> > &a, ll n, vector<vector<ll> > &x){
	if(n == 0) {
		for(int i=0; i<K; i++){
			for(int j=0; j<K; j++){
				if(i==j) x[i][j] = (1ll<<32)-1;
				else x[i][j] = 0;
			}
		}
		return;
	}
	if(n == 1) {
		for(int i=0; i<K; i++){
			for(int j=0; j<K; j++){
				x[i][j] = a[i][j];
			}
		}
		return;
	}
	vector<vector<ll> > tmp(K, vector<ll>(K));
	if(n%2 == 0) {
		matpow(a, n/2, tmp);
		matmul(tmp, tmp, x);
	}
	else {
		matpow(a, n-1, tmp);
		matmul(tmp, a, x);
	}
}

int main(){
	cin >> K >> M;
	for(int i=0; i<K; i++) cin >> A[i];
	for(int i=0; i<K; i++) cin >> C[i];

	if(M <= K){
		cout << A[M-1] << endl;
		return 0;
	}

	vector<vector<ll> > mat(K, vector<ll>(K));
	for(int i=0; i<K; i++){
		mat[0][i] = C[i];
	}
	for(int i=0; i<K-1; i++){
		mat[i+1][i] = (1ll<<32)-1;
	}
	//for(int i=0; i<K; i++){
	//	for(int j=0; j<K; j++){
	//		cout << mat[i][j] << (j==K-1?'\n':' ');
	//	}
	//}
	vector<vector<ll> > mat2(K, vector<ll>(K));
	matpow(mat, M-K, mat2);

	//for(int i=0; i<K; i++){
	//	for(int j=0; j<K; j++){
	//		cout << mat2[i][j] << (j==K-1?'\n':' ');
	//	}
	//}
	ll ans = 0;
	for(int i=0; i<K; i++){
		ans = ans ^ (A[i] & mat2[0][K-i-1]);
	}
	cout << ans << endl;

	return 0;
}
