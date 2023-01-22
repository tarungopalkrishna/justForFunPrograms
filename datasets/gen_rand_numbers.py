import random
import numpy as np


TYPE = "desc" # asc or desc : anything else generates random numbers
LOWER_LIMIT=0
UPPER_LIMIT=65536
LENGTH=5000000


def gen_numbers(length=5000, l_limit=0, u_limit=65536):
    return np.random.randint(l_limit, u_limit, length, np.int64)

def to_file(numbers: np.ndarray,filename="unsorted_numbers.txt"):
    with open(filename, "w") as fl:
        fl.write(" ".join(list(map(str,numbers))))

if __name__ == "__main__":
    num = gen_numbers(LENGTH, LOWER_LIMIT, UPPER_LIMIT)
    if TYPE == "desc":
        num = sorted(num, reverse=True)
        to_file(num, f"descending_numbers_{LENGTH}.txt")
    elif TYPE == "asc":
        num = sorted(num)
        to_file(num, f"ascending_numbers_{LENGTH}.txt")
    else:
        to_file(num, f"unsorted_numbers_{LENGTH}.txt")