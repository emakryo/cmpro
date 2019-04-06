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

int solve(){
	int N, B, F;
	cin >> N >> B >> F;
	string buf;
	string response[5];
	for(int k=0; k<5; k++){
		for(int i=0; i<N; i++){
			buf.push_back('0' + ((i/(1<<(4-k)))%2));
		}
		cout << buf << endl;
		buf.clear();
		cin >> response[k];
	}

	int i=0;
	vector<int> ans;
	for(int j=0; j<N/16+(N%16>0); j++){
		int k=0;
		while(i+k<N-B && response[0][i]==response[0][i+k]) k++;
		vector<bool> exist(16);;
		for(int l=0; l<k; l++){
			int x = 0;
			for(int p=1; p<5; p++){
				if(response[p][i+l]=='1'){
					x += 1<<(4-p);
				}
			}
			//cout << x << endl;
			exist[x] = true;
		}
		for(int l=0; l<16; l++){
			if(!exist[l] && j*16+l<N) ans.push_back(j*16+l);
		}
		i += k;
	}
	for(int i=0; i<B-1; i++) cout << ans[i] << ' ';
	cout << ans[B-1] << endl;
	int verdict;
	cin >> verdict;
	return verdict;
}

int main(){
	int T;
	cin >> T;
	for(int i=0; i<T; i++){
		if(solve()!=1) break;
	}

	return 0;
}
