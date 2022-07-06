from time import perf_counter
LENGTH=5000000


def insertion(numbers: list, order="asc"):
    arr_len = len(numbers)
    start = perf_counter()
    for i in range(1, arr_len):
        j = i-1
        while j >= 0 and numbers[i] < numbers[j]:
            numbers[j+1] = numbers[j]
            j -= 1
        numbers[j+1] = numbers[i]
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
    # numbers = read_numbers(file=f"../datasets/unsorted_numbers_{LENGTH}.txt")
    # numbers = read_numbers(file=f"../datasets/descending_numbers_{LENGTH}.txt")
    numbers = read_numbers(file=f"../datasets/ascending_numbers_{LENGTH}.txt")
    sorted_numbers = insertion(numbers=numbers)
    assert sorted(numbers) == sorted_numbers == numbers
    # print(sorted_numbers)