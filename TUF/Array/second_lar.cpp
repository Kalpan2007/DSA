#include <iostream>
#include <vector>
using namespace std;

int secondLargestElement(vector<int>& arr) {
        if (arr.size() < 2) return -1; 
        int max = INT_MIN;
        int sm = INT_MIN;
        for(int val : arr){
            if(max<val){
                sm = max;
                max = val;
            }
            else if(val < max && val > sm){
                sm = val ;
            }
        }
         return (sm == INT_MIN) ? -1 : sm;
    }

int main(){
    vector<int> arr = {3, 5, 1, 8, 2};
    cout << secondLargestElement(arr);
    return 0;
}