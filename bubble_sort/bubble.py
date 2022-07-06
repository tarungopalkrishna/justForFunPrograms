from time import perf_counter
LENGTH=5000


def bubble(numbers: list, order="asc"):
    arr_len = len(numbers)
    start = perf_counter()
    for i in range(arr_len-1):
        for j in range(arr_len-i-1):
            if(numbers[j] > numbers[j+1]):
                numbers[j+1], numbers[j] = numbers[j], numbers[j+1]
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
    sorted_numbers = bubble(numbers=numbers)
    assert sorted(numbers) == sorted_numbers
    # print(sorted_numbers)