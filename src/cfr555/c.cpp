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
const int Nmax=2e5;
int N, A[Nmax];

int main(){
	cin >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	string s;
	int l=0, r=N-1;
	int last = 0;
	while(l<r){
		//cout << last << " " << A[l] << " " << A[r] << endl;
		if(last < A[l] && (A[l] < A[r] || A[r] <= last)){
			s += "L";
			last = A[l];
			l++;
		} else if(last < A[r] && (A[l] > A[r] || A[l] <= last)){
			s += "R";
			last = A[r];
			r--;
		} else {
			break;
		}
	}
	//cout << l << " " << r << endl;

	if(l==r && A[l]>last){
		s += "L";
	} else if(A[l]==A[r] && A[l] > last){
		int i=l;
		while(A[i+1]>A[i]) i++;
		int nl = i - l + 1;
		i=r;
		while(A[i-1]>A[i]) i--;
		int nr = r - i + 1;

		//cout << nl << " " << nr << endl;

		if(nr>nl){
			for(int i=0; i<nr; i++) s += "R";
		} else{
			for(int i=0; i<nl; i++) s += "L";
		}
	}
	cout << s.size() << endl;
	cout << s << endl;

	return 0;
}
