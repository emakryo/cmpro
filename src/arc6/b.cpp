#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int Lmax = 20;
int N, L;
vector<int> bar[Lmax];

int main(){
	cin >> N >> L;
	vector<int> idx(N);
	for(int i=0; i<N; i++) idx[i] = i+1;

	string s;
	getline(cin, s);
	for(int i=0; i<L; i++){
		getline(cin, s);
		for(int j=1; j<s.size(); j+=2){
			if(s[j] == '-'){
				int k = (j-1)/2;
				swap(idx[k], idx[k+1]);
			}
		}
		//for(int j=0; j<N; j++) cout << idx[j] << ' ';
		//cout << endl;
	}

	getline(cin, s);
	for(int j=0; j<s.size(); j+=2){
		if(s[j] == 'o'){
			cout << idx[j/2] << endl;
		}
	}

	return 0;
}
