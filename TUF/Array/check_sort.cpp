#include <iostream>
#include <vector>
using namespace std;

bool check_sorted(vector<int>& arr){
    int n = arr.size();
    for(int i = 0 ; i<n-1 ;i++){
        if(arr[i]>arr[i+1]){
            return false;
        }
    }
    return true;
}

int main(){
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << check_sorted(arr);
    return 0;
}