#include<iostream>
using namespace std;

int main(){
    long A,B,C;
    cin >> A >> B >> C;
    if(A%2 == 0 || B%2 == 0 || C%2 == 0) cout << 0 << endl;
    else if(A <= C && B <= C) cout << A*B << endl;
    else if(A <= B && C <= B) cout << A*C << endl;
    else cout << B*C << endl;

    return 0;
}
