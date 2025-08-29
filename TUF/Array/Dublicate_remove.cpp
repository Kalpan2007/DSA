// dublicate remove form array
#include <iostream>
#include <vector>
using namespace std;

int remove_dublicate(vector<int>& arr){
    int i = 0;
    for(int j = 1 ; j < arr.size();j++){
        if(arr[i] != arr[j]){
            i++;
            arr[i] = arr[j];
        }
    }
    return i +1;
}

int main(){
    vector<int> arr = {1, 2, 2, 3, 4, 4, 5};
    int new_size = remove_dublicate(arr);
    cout << "New size after removing duplicates: " << new_size << endl;
    cout << "Array after removing duplicates: ";
    for(int i = 0; i < new_size; i++){
        cout << arr[i] << " ";
    }
    return 0;
}