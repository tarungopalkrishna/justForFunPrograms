from time import perf_counter
LENGTH=5000


def get_pivot(numbers: list) -> int:
    return len(numbers)//2

def merge_sort(numbers: list):
    if len(numbers) > 1:
        pivot = get_pivot(numbers)
        left = numbers[:pivot]
        right = numbers[pivot:]

        merge_sort(numbers=left)
        merge_sort(numbers=right)

        i = j = k = 0
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                numbers[k] = left[i]
                i += 1
            else:
                numbers[k] = right[j]
                j += 1
            k += 1

        while i < len(left):
            numbers[k] = left[i]
            i += 1
            k += 1
        while j < len(right):
            numbers[k] = right[j]
            j += 1
            k += 1



def read_numbers(file="../datasets/unsorted_numbers.txt"):
    # print(f"Reading from file {file}")
    with open(file) as fl:
        numbers = fl.readlines()
        # print(numbers)
        numbers = " ".join(numbers)
        numbers = numbers.split(" ")
        # print(numbers)
        return list(map(int, numbers))


if __name__ == "__main__":
    numbers = read_numbers(file=f"../datasets/unsorted_numbers_{LENGTH}.txt")
    # numbers = read_numbers(file=f"../datasets/descending_numbers_{LENGTH}.txt")
    # numbers = read_numbers(file=f"../datasets/ascending_numbers_{LENGTH}.txt")
    start = perf_counter()
    merge_sort(numbers=numbers)
    print(f"The total time to sort {LENGTH} elements is {perf_counter() - start}")
    # print(numbers)
    assert sorted(numbers) == numbers
    # print(sorted_numbers)