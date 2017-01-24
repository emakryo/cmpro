#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
typedef long long ll;
string C[4];

int main(){
    for(int i=0; i<4; i++) getline(cin, C[i]);
    for(int i=0; i<4; i++){
        for(int j=0; j<C[3-i].size(); j++){
            cout << C[3-i][C[3-i].size()-1-j];
        }
        cout << endl;
    }
    return 0;
}
