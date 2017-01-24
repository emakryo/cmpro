#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
string t[3] = {"TAKAHASHIKUN", "Takahashikun", "takahashikun"};

int main(){
	int N;
	int ans=0;
	cin >> N;
	for(int i=0; i<N; i++){
		string w;
		cin >> w;
		if(i == N-1){
			w = w.substr(0, w.size()-1);
		}
		for(int i=0; i<3; i++){
			ans += t[i] == w ? 1 : 0;
		}
	}
	cout << ans << endl;
	return 0;
}
