#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
	string sep = " ";
	if(v.size()) os << v[0];
	for(int i=1; i<v.size(); i++) os << sep << v[i];
	return os;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

char to_lower(char x){
	return x-'A'+'a';
}
char to_upper(char x){
	return x-'a'+'A';
}

int main() {
	ios_base::sync_with_stdio(false);
	string s;
	cin >> s;

	vector<string> w;
	string tmp;
	tmp.push_back(to_lower(s[0]));
	int k=1;
	while(k<s.size()){
		if('a'<=s[k]&&s[k]<='z'){
			tmp.push_back(s[k]);
		} else {
			tmp.push_back(to_lower(s[k]));
			w.push_back(tmp);
			k++;
			if(k<s.size()) tmp = string(1, to_lower(s[k]));
		}
		k++;
	}
	sort(w.begin(), w.end());
	for(string v: w){
		for(int i=0; i<v.size(); i++){
			if(i==0||i==v.size()-1) cout << to_upper(v[i]);
			else cout << v[i];
		}
	}
	cout << endl;


	return 0;
}
