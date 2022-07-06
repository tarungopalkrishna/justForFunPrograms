#include<vector>
#include<iostream>

using namespace std;

void insertEnds(int num, std::vector<int>& arr){
    arr.push_back(num);
    int i = arr.size()-2;
    while(num < arr[i] && i>=0){
        arr[i+1] = arr[i];
        arr[i] = num;
        i--;
    }
}

void showEnds(std::vector<int>& arr){
    std::cout << std::endl << "1********" << std::endl;
    for(int i=0;i<arr.size();i++){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl <<  "2********" << std::endl;
}

int main(int argc, char **argv){
    std::vector<int> arr;
    insertEnds(8, arr);
    insertEnds(1, arr);
    insertEnds(2, arr);
    insertEnds(6, arr);
    insertEnds(3, arr);
    insertEnds(7, arr);
    insertEnds(4, arr);
    insertEnds(10, arr);
    insertEnds(5, arr);
    insertEnds(9, arr);
    showEnds(arr);
    return 0;
}