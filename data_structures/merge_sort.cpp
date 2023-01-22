#include<iostream>
#include<vector>

using namespace std;



std::vector<int> randn(){
    //std::vector<int> a = {1,2,3,4,5,6};
    std::vector<int> a = {6,5,4,3,2,1};
    return a;
}

size_t get_split_point(size_t start, size_t end){
    return (start+end)/2;
}


void merge_sort(std::vector<int> arr, size_t start, size_t end){
    for(auto i = start; i< end; i++){
        std::cout << arr[i] << " ";
    std::cout<< std::endl;
    }
    size_t split_point = get_split_point(start, end);

    merge_sort(arr
}


int main(){
    std::vector<int> array;
    array = randn();
    merge_sort(array, 0, sizeof(array) / sizeof(int));
    return 0;
}
