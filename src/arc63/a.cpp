#include<iostream>
using namespace std;
string S;

int main(){
	cin >> S;

	char c = S[0];
	int cnt = 0;
	for(int i=1; i<S.size(); i++){
		if(c != S[i]){
			c = S[i];
			cnt++;
		}
	}

	cout << cnt << endl;
}
