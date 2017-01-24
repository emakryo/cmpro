#include<iostream>
using namespace std;

int main(){
	string s;
	cin >> s;

	int c=0;
	int ans=0;
	for(int i=0; i<s.size(); i++){
		if(c==0){
			c++;
			if(s[i]=='p') ans -=1;
		}
		else{
			if(s[i]=='g'){
				ans +=1;
				c--;
			}
			else{
				c--;
			}
		}
	}

	cout << ans << endl;
}
