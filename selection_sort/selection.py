from time import perf_counter
LENGTH=50000


def insertion(numbers: list, order="asc"):
    arr_len = len(numbers)
    start = perf_counter()
    for i in range(arr_len-1):
        min_index = i
        for j in range(min_index+1, arr_len):
            if(numbers[j] < numbers[min_index]):
                min_index = j
        numbers[i], numbers[min_index] = numbers[min_index], numbers[i]
    print(f"The total time to sort {LENGTH} elements is {perf_counter() - start}")
    return numbers


def read_numbers(file="../datasets/unsorted_numbers.txt"):
    # print(f"Reading from file {file}")
    with open(file) as fl:
        numbers = fl.readlines()
        # print(numbers)
        numbers = " ".join(numbers)
        numbers = numbers.split(" ")
        return list(map(int, numbers))


if __name__ == "__main__":
    numbers = read_numbers(file=f"../datasets/unsorted_numbers_{LENGTH}.txt")
    sorted_numbers = insertion(numbers=numbers)
    assert sorted(numbers) == sorted_numbers
    # print(sorted_numbers)