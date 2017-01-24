#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int A,B;

int main(){
	cin >> A >> B;

	int ans = 0;
	int d = abs(A-B);

	while(d >= 10){
		d /= 10;
		ans++;
	}

	while(d >= 5){
		d /= 5;
		ans++;
	}

	while(d >= 1){
		d /= 1;
		ans++;
		cout<<1<<endl;
	}

	cout << ans << endl;
	return 0;
}
