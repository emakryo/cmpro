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

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
    for(int i=0; i<v.size(); i++) is >> v[i];
    return is;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
    cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

// accepts a string with lower alphabets.
struct Trie {
    struct Node {
        vector<Node*> children;
        vector<int> count;  // keep the number of suffix string containing each alphabet.
        Node(int n_char){
            children.assign(n_char, NULL);
            count.assign(n_char, 0);
        }
        vector<bool> add(const string &s, int idx){
            if(idx==s.size()) return vector<bool>(children.size());
            int c = s[idx]-'a';
            if(children[c] == NULL){
                Node* next = new Node(children.size());
                children[c] = next;
            }
            vector<bool> cnt = children[c]->add(s, idx+1);
            cnt[c] = true;
            for(int i=0; i<cnt.size(); i++){
                if(cnt[i]) count[i]++;
            }
            return cnt;
        }

        Node* find(const string &s, int idx){
            if(idx==s.size()) return this;
            int c = s[idx]-'a';
            if(children[c]==NULL){
                return NULL;
            }
            return children[c]->find(s, idx+1);
        }
    };
    Node* root;

    Trie(int n=26) {
        root = new Node(n);
    }

    void add(const string &s){
        root->add(s, 0);
    }

    Node* find(const string &s){
        return root->find(s, 0);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n; cin >> n;
    vector<pair<int, string>> s(n);
    for(int i=0; i<n; i++){
        string si;
        cin >> si;
        reverse(si.begin(), si.end());
        s[i] = {si.size(), si};
    }
    sort(s.rbegin(), s.rend());

    Trie trie;
    ll ans = 0;
    for(int i=0; i<n; i++){
        string si = s[i].second;
        dbg(si);
        Trie::Node* node = trie.root;
        if(si.size()>1) node = trie.find(si.substr(0, si.size()-1));
        if(node != NULL){
            ans += node->count[si.back()-'a'];
            dbg(node->count);
        }
        trie.add(si);
    }

    cout << ans << endl;
    return 0;
}