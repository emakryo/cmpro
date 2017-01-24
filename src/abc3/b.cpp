#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
string S,T;

int main(){
	cin >> S >> T;

	bool ans = true;
	for(int i=0; i<S.size(); i++){
		if(S[i] == '@'){
			if(!(T[i] == '@' ||
				T[i] == 'a' ||
				T[i] == 't' ||
				T[i] == 'c' ||
				T[i] == 'o' ||
				T[i] == 'd' ||
				T[i] == 'e' ||
				T[i] == 'r')){
				ans = false;
				break;
			}
		}
		else if(T[i] == '@'){
			if(!(S[i] == '@' ||
				S[i] == 'a' ||
				S[i] == 't' ||
				S[i] == 'c' ||
				S[i] == 'o' ||
				S[i] == 'd' ||
				S[i] == 'e' ||
				S[i] == 'r')){
				ans = false;
				break;
			}
		}
		else{
			if(S[i] != T[i]){
				ans = false;
				break;
			}
		}
	}

	if(ans){
		cout << "You can win" << endl;
	}
	else{
		cout << "You will lose" << endl;
	}

	return 0;
}
