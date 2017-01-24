#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
#include<string>
using namespace std;
typedef long long ll;
const int HWmax = 1000;
const char *A[] = {
	"..o..",
	".o.o.",
	"o...o",
	"ooooo",
	"o...o"};
const char *B[] = {
	"oooo.",
	"o...o",
	"oooo.",
	"o...o",
	"oooo."};
const char *C[] = {
	".ooo.",
	"o...o",
	"o....",
	"o...o",
	".ooo."};
int H,W;
string X[HWmax];
int rect[HWmax][HWmax];
bool done[HWmax][HWmax];

bool match(int s, int x, int y, const char *c[]){
	int ok = true;
	for(int i=0; i<5*s; i++){
		for(int j=0; j<5*s; j++){
			if(X[x+i][y+j] != c[i/s][j/s]){
				ok = false;
				break;
			}
		}
		if(!ok) break;
	}
	if(ok) return true;

	ok = true;
	for(int i=0; i<5*s; i++){
		for(int j=0; j<5*s; j++){
			if(X[x+i][y+j] != c[4-j/s][i/s]){
				ok = false;
				break;
			}
		}
		if(!ok) break;
	}
	if(ok) return true;

	ok = true;
	for(int i=0; i<5*s; i++){
		for(int j=0; j<5*s; j++){
			if(X[x+i][y+j] != c[4-i/s][4-j/s]){
				ok = false;
				break;
			}
		}
		if(!ok) break;
	}
	if(ok) return true;

	ok = true;
	for(int i=0; i<5*s; i++){
		for(int j=0; j<5*s; j++){
			if(X[x+i][y+j] != c[j/s][4-i/s]){
				ok = false;
				break;
			}
		}
		if(!ok) break;
	}
	if(ok) return true;

	return false;
}

int main(){
	cin >> H >> W;
	for(int i=0; i<H; i++){
		cin >> X[i];
	}

	for(int i=0; i<H+W-1; i++){
		for(int j=0; j<H; j++){
			int x = j;
			int y = i-j;
			if(y < 0 || W <= y) continue;
			int c = X[x][y] == 'o' ? 1 : 0;
			if(x == 0 && y == 0) rect[x][y] = c;
			else if(x == 0) rect[x][y] = rect[x][y-1] + c;
			else if(y == 0) rect[x][y] = rect[x-1][y] + c;
			else rect[x][y] = rect[x][y-1] + rect[x-1][y] - rect[x-1][y-1] + c;
		}
	}

	/*
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			cout << rect[i][j] << " ";
		}
		cout << endl;
	}
	*/

	int nA=0, nB=0, nC=0;
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			nA += A[i][j] == 'o' ? 1 : 0;
			nB += B[i][j] == 'o' ? 1 : 0;
			nC += C[i][j] == 'o' ? 1 : 0;
		}
	}


	int aA=0, aB=0, aC=0;
	for(int i=1; i*7<=min(H,W); i++){
		for(int x=0; x<=H-i*7; x++){
			for(int y=0; y<=W-i*7; y++){
				/*
				if(done[x][y] || done[x+i*7][y+i*7] ||
						done[x][y*i*7] || done[x+i*7][y]) continue;
						*/
				int p = rect[x+i*7-1][y+i*7-1];
				if(x > 0) p -= rect[x-1][y+i*7-1];
				if(y > 0) p -= rect[x+i*7-1][y-1];
				if(x > 0 && y > 0) p += rect[x-1][y-1];
				int q = rect[x+i*6-1][y+i*6-1] - rect[x+i-1][y+i*6-1]
					- rect[x+i*6-1][y+i-1] + rect[x+i-1][y+i-1];
				if(p != q) continue;
				//cout << x << " " << y << " " << p << " " << q << endl;
				if(p == i*i*nA && match(i, x+i, y+i, A)) aA++;
				if(p == i*i*nB && match(i, x+i, y+i, B)) aB++;
				if(p == i*i*nC && match(i, x+i, y+i, C)) aC++;
			}
		}
	}

	cout << aA << " " << aB << " " << aC << endl;

	return 0;
}
