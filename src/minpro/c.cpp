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
const int Nmax = 100000;
int N,K;
int A[Nmax];
string S[Nmax];

struct node{
	node *children[26];
	int all, search;
};

int main(){
	cin >> N >> K;
	for(int i=0; i<K; i++) cin >> A[i];

	node root;
	for(int i=0; i<26; i++) root.children[i] = NULL;
	root.all=0;
	root.search=0;
	for(int i=0; i<N; i++){
		cin >> S[i];
		string s=S[i];
		node *n=&root;
		for(int j=0; j<s.size(); j++){
			node *m;
			n->all++;
			if(n->children[s[j]-'a']==NULL){
				n->children[s[j]-'a'] = new node;
				m = n->children[s[j]-'a'];
				for(int k=0; k<26; k++) m->children[k] = NULL;
				m->all=0;
				m->search=0;
			}
			else{
				m=n->children[s[j]-'a'];
			}
			n = m;
		}
		n->all++;
	}

	for(int i=0; i<K; i++){
		int j=A[i]-1;
		node *n=&root;
		for(int k=0; k<S[j].size(); k++){
			string s=S[j];
			n->search++;
			n=n->children[s[k]-'a'];
		}
		n->search++;
	}

	if(N==K){
		cout << endl;
		return 0;
	}

	node *n=&root;
	string ans = "";
	while(true){
		node *next=NULL;
		for(int i=0; i<26; i++){
			node *m=n->children[i];
			if(m == NULL) continue;
			if(m->search==K && m->all==K){
				cout << ans << (char)('a'+i) << endl;
				return 0;
			}
			if(m->search==K){
				next = m;
				ans += 'a'+i;
			}
		}
		if(next==NULL) break;
		n = next;
	}
	cout << -1 << endl;

	return 0;
}
