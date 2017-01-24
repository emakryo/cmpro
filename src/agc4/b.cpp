#include<iostream>
#include<algorithm>
using namespace std;
int N;
long X, A[2000];
long b[2000];

int main(){
    cin >> N >> X;
    for(int i=0; i<N; i++){
        cin >> A[i];
        b[i] = 1e15;
    }

    long min_sum = 1e15;
    for(int i=0; i<N; i++){
        long sum = 0;
        for(int j=0; j<N; j++){
            b[j] = min(A[(j-i+N)%N],b[j]);
            sum += b[j];
        }
        sum += i*X;
        min_sum = min(min_sum, sum);
    }

    cout << min_sum << endl;

    return 0;
}
