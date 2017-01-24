#include<iostream>
#include<algorithm>
using namespace std;
string N;
int K,D[10];

int find_least(char n){
	char i=n;
	while(i <= '9' && D[i-'0'] > 0) i++;
	return D[i-'0'] > 0 ? -1 : i;
}

int main(){
	cin >> N >> K;
	for(int i=0; i<K; i++){
		int d;
		cin >> d;
		D[d] = 1;
	}

	string ans;

	char l = find_least('0');
	char m = find_least('1');
	if(find_least(N[0]) < 0){
		ans += m;
		for(int j=0; j<N.size(); j++) ans += l;
		cout << ans << endl;
		return 0;
	}
	int i=0;
	while(i < N.size() && D[N[i]-'0'] == 0){
		ans += N[i];
		i++;
	}
	if(D[N[i]-'0'] == 0) {
		cout << ans << endl;
		return 0;
	}
	while(i > 0 && find_least(N[i]+1) < 0) {
		i--;
		ans.erase(i,1);
	}
	if(i == 0 && find_least(N[0]+1) < 0){
		ans += m;
		for(int j=0; j<N.size(); j++) ans += l;
		cout << ans << endl;
		return 0;
	}
	ans += find_least(N[i++]+1);
	while(i < N.size()) {
		ans += l;
		i++;
	}
	cout << ans << endl;

	return 0;
}
