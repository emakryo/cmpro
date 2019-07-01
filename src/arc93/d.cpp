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
int A, B;

int main(){
    cin >> A >> B;

    vector<string> ans;
    string buf(100, '#');
    for(int i=0; i<A-1; i++){
        buf[2*(i%50)] = '.';
        if(i%50==49){
            ans.push_back(buf);
            ans.push_back(string(100, '#'));
            buf = string(100, '#');
        }
    }
    ans.push_back(buf);
    ans.push_back(string(100, '#'));

    buf = string(100, '.');
    for(int i=0; i<B-1; i++){
        buf[2*(i%50)] = '#';
        if(i%50==49){
            ans.push_back(string(100, '.'));
            ans.push_back(buf);
            buf = string(100, '.');
        }
    }
    ans.push_back(string(100, '.'));
    ans.push_back(buf);

    printf("%d 100\n", ans.size());
    for(string s: ans){
        printf("%s\n", s.c_str());
    }

    return 0;
}