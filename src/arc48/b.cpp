#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
const int Nmax = 1e6;
int R[Nmax], H[Nmax];

int main(){

	cin >> N;
	for(int i=0; i<N; i++) cin >> R[i] >> H[i];

	vector<pair<int, int>> a(N);
	for(int i=0; i<N; i++) a[i] = {R[i], i};
	sort(a.begin(), a.end());

	int start = 0, end = 0;
	vector<int> win(N), lose(N), draw(N);
	while(start<N){
		end = lower_bound(a.begin(), a.end(), pair<int, int>({a[start].first+1, 0}))-a.begin();
		int cnt[4] = {0, 0, 0, 0};
		for(int i=start; i<end; i++){
			cnt[H[a[i].second]]++;
		}
		for(int i=start; i<end; i++){
			int m = a[i].second;
			if(H[m] == 1){
				win[m] = start+cnt[2];
				lose[m] = N-end+cnt[3];
				draw[m] = cnt[1]-1;
			} else if(H[m]==2){
				win[m] = start+cnt[3];
				lose[m] = N-end+cnt[1];
				draw[m] = cnt[2]-1;
			} else {
				win[m] = start+cnt[1];
				lose[m] = N-end+cnt[2];
				draw[m] = cnt[3]-1;
			}
		}
		start = end;
	}

	for(int i=0; i<N; i++){
		cout << win[i] << " " << lose[i] << " " << draw[i] << endl;
	}

	return 0;
}
