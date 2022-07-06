#include<iostream>
#include<fstream>
#include<vector>
#include<string>


// Binary search
// Time complexity: O(log(n))
// Space complexity: O(1)
// int binarySearch(std::vector<int>& arr, int num){
//     int left = 0;
//     int right = arr.size()-1;
//     while(left <= right){
//         int mid = left + (right-left)/2;
//         if(arr[mid] == num){
//             return mid;
//         }
//         else if(arr[mid] < num){
//             left = mid+1;
//         }
//         else{
//             right = mid-1;
//         }
//     }
//     return -1;
// }



int binarySearch(std::vector<int> &arr, int number){
    int start = 0, end = arr.size()-1, mid = (start+end)/2;
    while(start <= end){
        mid = (start+end)/2;
        if(arr[mid] == number){
            return mid;
        } else if(arr[mid] < number){
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return -1;
}

// Read numbers from a file seperated by a space
// Time complexity: O(n)
// Space complexity: O(n)
std::vector<int> getSortedNumber(std::string fileName){
    // Isnt this a local instance of the variable?
    std::vector<int> numbers;
    std::ifstream file(fileName);
    int num;
    // Check if the file is not empty
    if(!(file.peek() == std::ifstream::traits_type::eof())){
        // return numbers;
        while(file >> num){
            numbers.push_back(num);
        }
    }
    return numbers;
}



int main(int argc, char *argv[]){
    if(argc == 2){
        std::vector<int> numbers = getSortedNumber("./sorted_numbers.txt");
        if(numbers.empty()){
            std::cout << "File is empty!" << std::endl;
        }
        else{
            // std::cout << "The first element is:" << numbers[0] << std::endl;
            int loc = binarySearch(numbers, atoi(argv[1]));
            if(loc == -1){
                std::cout << "Number not found!" << std::endl;
            }
            else{
                std::cout << "Number found at location: " << loc << std::endl;
            }
        }
    } else {
        std::cout << "Incorrect number of arguments!" << std::endl;
    }
    // std::cout << binarySearch(numbers, 5) << std::endl;
    return 0;
}