#include <iostream>
#include <vector>
using namespace std;

int largest(vector<int>& arr){
    int n = arr.size();
    if(n==0) return -1;
    int max = arr[0];
    for(int num : arr){
        if(num > max){
            max = num;
        }
    }
    return max;
}

int main(){
    vector<int> arr = {3, 5, 1, 8, 2};
    cout << largest(arr);
    return 0;
}