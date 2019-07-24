#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;
string S, T;

int main(){
	cin >> S;
	cin >> T;
	int N = S.size();

	map<char, char> m_st, m_ts;
	for(int i=0; i<N; i++){
		if(m_st.find(S[i])==m_st.end()){
			m_st[S[i]] = T[i];
		} else if(m_st[S[i]]!=T[i]){
			cout << "No" << endl;
			return 0;
		}
		if(m_ts.find(T[i])==m_ts.end()){
			m_ts[T[i]] = S[i];
		} else if(m_ts[T[i]]!=S[i]){
			cout << "No" << endl;
			return 0;
		}
	}

	cout << "Yes" << endl;

	return 0;
}
