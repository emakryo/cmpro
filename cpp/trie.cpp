#include<bits/stdc++.h>

// accepts a string with lower alphabets.
struct Trie {
    struct Node {
        std::vector<Node*> children;
        std::vector<int> count;  // keep the number of suffix string containing each alphabet.
        Node(int n_char){
            children.assign(n_char, NULL);
            count.assign(n_char, 0);
        }
        std::vector<bool> add(const std::string &s, int idx){
            if(idx==s.size()) return std::vector<bool>(children.size());
            int c = s[idx]-'a';
            if(children[c] == NULL){
                Node* next = new Node(children.size());
                children[c] = next;
            }
            std::vector<bool> cnt = children[c]->add(s, idx+1);
            cnt[c] = true;
            for(int i=0; i<cnt.size(); i++){
                if(cnt[i]) count[i]++;
            }
            return cnt;
        }

        Node* find(const std::string &s, int idx){
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

    void add(const std::string &s){
        root->add(s, 0);
    }

    Node* find(const std::string &s){
        return root->find(s, 0);
    }
};
