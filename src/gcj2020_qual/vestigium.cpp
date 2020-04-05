#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
	int N;
	cin >> N;
	vector<vector<int>> M(N, vector<int>(N));
	for(int i=0; i<N; i++) for(int j=0; j<N; j++){
		cin >> M[i][j];
	}

	int k = 0;
	for(int i=0; i<N; i++) k+=M[i][i];
	int r = 0;
	for(int i=0; i<N; i++){
		bool dup = false;
		vector<int> cnt(N+1);
		for(int j=0; j<N; j++){
			if(cnt[M[i][j]]>0) dup=true;
			cnt[M[i][j]]++;
		}
		if(dup) r++;
	}
	int c = 0;
	for(int j=0; j<N; j++){
		bool dup = false;
		vector<int> cnt(N+1);
		for(int i=0; i<N; i++){
			if(cnt[M[i][j]]>0) dup=true;
			cnt[M[i][j]]++;
		}
		if(dup) c++;
	}

	cout << k << " " << r << " " << c << endl;
}

int main(){
	int T;
	cin >> T;
	for(int t=0; t<T; t++){
		cout << "Case #" << t+1 << ": ";
		solve();
	}

	return 0;
}
