#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void selection_sort(vector<int>& arr){
    int n = arr.size();
    for(int i = 0 ; i < n-1 ; i++){
        int min = i;
        for(int j = i+1;j<n;j++){
            if(arr[j]<arr[min]){
                min = j;
            }
        }
        if (min != i) {
            swap(arr[i], arr[min]);
        }
    }
}
void bubble_sort(vector<int>& arr){
    int n = arr.size();
    for(int i = n-1 ; i>0 ; i--){
        int sorted = 0;
        for(int j = 0;j<i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                sorted = 1;
            }
            if(sorted==0){
                break;
            }
        }
    }
}
void insertion_sort(vector<int>& arr){
    int n = arr.size();
    for(int i =0;i<n;i++){
        int j = i;
        while(j>0 && arr[j-1] > arr[j]){
            swap(arr[j-1],arr[j]);
            j--;
        }
    }
}
void merge(vector<int>& arr, int low , int mid , int high){
    vector<int> temp;
    int left = low;\
    int right = mid +1;
    while(left <= mid && right <= high){
        if(arr[left] < arr[right]){
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            right++;
        }
    }
    while(left <= mid){
        temp.push_back(arr[left]);
        left++;
    }
    while(right <= high){
        temp.push_back(arr[right]);
        right++;
    }
    for(int i = low; i <= high; i++){
        arr[i] = temp[i - low];
    }
}
void merge_sort(vector<int>& arr , int low , int  high){
    if(low==high) return ;
    int mid = (low + high ) / 2;
    merge_sort(arr,low,mid);
    merge_sort(arr,mid+1,high);
    merge(arr, low, mid, high);
}
int partition(vector<int>& arr,int low,int high){
    int pivot = arr[low];
    int i = low;
    int j = high;
    while(i<j){
        while(arr[i]<=pivot && i <=high){
            i++;
        }
        while(arr[j]>pivot && j>=low){
            j--;
        }
        if(i<j){
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[low],arr[j]);
    return j;
}
void quick_sort(vector<int>& arr,int low,int high){
    if(low<high){
        int p_index = partition(arr,low,high);
        quick_sort(arr,low,p_index-1);
        quick_sort(arr,p_index+1,high);
    }
}
int main() {
    vector<int> arr = {45,12,48,3,56};
    // selection_sort(arr);
    // bubble_sort(arr);
    // insertion_sort(arr);
    //  merge_sort(arr, 0, arr.size() - 1);
    quick_sort(arr, 0, arr.size() - 1);
     for (int num : arr) {
        cout << num << " ";
    }
    return 0;
}