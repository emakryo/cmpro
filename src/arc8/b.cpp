#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;

int main(){
	int n,m;
	string name, kit;
	cin >> n >> m;
	cin >> name >> kit;
	vector<int> v(26), w(26);
	for(int i=0; i<n; i++) v[name[i]-'A']++;
	for(int i=0; i<m; i++) w[kit[i]-'A']++;

	int ans = 1;
	for(int i=0; i<n; i++){
		int k = name[i]-'A';
		if(w[k] == 0){
			cout << -1 << endl;
			return 0;
		}
		ans = max(ans, (int)ceil((double)v[k]/w[k]));
	}

	cout << ans << endl;

	return 0;
}
