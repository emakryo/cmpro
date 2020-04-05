#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int get_bit(int p){
	cout << p+1 << endl;
	//cerr << p+1 << endl;
	int x;
	cin >> x;
	return x;
}

void check_range(vector<int> &buf, int start, int end){
	int b = buf.size();
	end = min(end, (b+1)/2);
	bool comp_xor_reverse = false;
	for(int i=start; i<end; i++){
		if(buf[i]!=buf[b-i-1]){
			int a = get_bit(i);
			if(a!=buf[i]) comp_xor_reverse = true;
			break;
		}
		if(i==end-1) get_bit(0);
	}
	bool comp = false;
	for(int i=start; i<end; i++){
		if(buf[i]==buf[b-i-1]){
			int a = get_bit(i);
			if(a!=buf[i]) comp = true;
			break;
		}
		if(i==end-1) get_bit(0);
	}

	bool reverse = comp ^ comp_xor_reverse;
	for(int i=start; i<end; i++){
		if(comp){
			buf[i] = 1-buf[i];
			buf[b-i-1] = 1-buf[b-i-1];
		}
		if(reverse){
			swap(buf[i], buf[b-i-1]);
		}
	}
}

void solve(int b){
	vector<int> buf(b);
	for(int k=0; k<(b+9)/10; k++){
		for(int i=5*k; i<5*(k+1); i++){
			if(i<(b+1)/2){
				buf[i] = get_bit(i);
				buf[b-i-1] = get_bit(b-i-1);
			} else {
				get_bit(0);
				get_bit(0);
			}
		}
	}

	for(int k=0; k<10; k++){
		if(5*k>=(b+1)/2) break;
		check_range(buf, 5*k, 5*(k+1));
	}
	check_range(buf, 0, 25);
	check_range(buf, 25, 50);

	for(int i=0; i<b; i++) cout << buf[i];
	cout << endl;
}

int main(){
	int T, B;
	cin >> T >> B;
	for(int t=1; t<=T; t++){
		solve(B);
		string judge;
		cin >> judge;
		if(judge!="Y") break;
	}

	return 0;
}
