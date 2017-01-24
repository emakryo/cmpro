#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int INF = 1e8;
int N;

int dfs(vector<int> &x, int n, int ans){
	//cout << x.size() << " " << n << endl;
	int s = x.size();
	if(s == n+1){
		int a = 0, b = 0;
		for(int i=0; i<s; i+=2){
			a *= 10;
			a += x[i];
		}
		for(int i=1; i<s; i+=2){
			b *= 10;
			b += x[i];
		}
		//cout << a << " " << b << endl;
		if(x[0] == 0 && s >= 3) return ans;
		if(x[1] == 0 && s >= 4) return ans;
		return min(ans, abs(a-b));
	}
	else{
		if((s-n) % 2 == 0){
			int a = 0, b = 0;
			int base = 1;
			for(int i=0; i<(s-n)/2; i++) base *= 10;
			for(int i=0; i<n; i+=2){
				a *= 10;
				a += x[i];
			}
			for(int i=1; i<n; i+=2){
				b *= 10;
				b += x[i];
			}
			a *= base;
			b *= base;
			if(a > b){
				b += base;
				if(a-(b-1) > ans){
					return ans;
				}
			}
			else{
				a += base;
				if(b-(a-1) > ans){
					return ans;
				}
			}
		}
		for(int i=n; i<x.size(); i++){
			swap(x[i], x[n]);
			/*
			for(int j=0; j<x.size(); j++){
				cout << y[j] << " ";
			}
			cout << endl;
			*/
			ans = min(ans, dfs(x, n+1, ans));
			swap(x[i], x[n]);
		}
		return ans;
	}
}

int main(){
	cin >> N;
	string s;
	getline(cin, s);

	for(int i=0; i<N; i++){
		int k = 0;
		vector<int> digit;
		getline(cin, s);
		for(int j=0; j<s.size(); j++){
			if('0' <= s[j] && s[j] <= '9'){
				digit.push_back(s[j]-'0');
			}
		}
		//for(int j=0; j<digit.size(); j++) cout << digit[j] << endl;

		cout << dfs(digit, 0, 1e8) << endl;
	}
	return 0;
}
