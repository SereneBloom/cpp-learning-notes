#include <iostream>
#include <vector>
using namespace std;

int ans(int *A, int n){
    vector<int>Count(n+1);
    for(int i = 0; i < n; i++){
        Count[A[i]] ++;
        if(Count[A[i]] > n / 2){
            return A[i];
        }
    }
    return -1;
}