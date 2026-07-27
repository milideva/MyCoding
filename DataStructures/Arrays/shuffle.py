from random import randint
from pprint import pprint

def shuffle (arr) :
    """
    Fisher-Yates Shuffle Algorithm (Classic Countdown Implementation)
    
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary
    
    Algorithm:
    - Iterate backwards from the last element (n-1) down to index 1.
    - Pick a random index 'j' between 0 and 'i' (inclusive).
    - Swap the element at current index 'i' with the element at random index 'j'.
    - This guarantees that every permutation is equally likely (unbiased).
    """
    n = len(arr)
    for i in range(n - 1, 0, -1):
        j = randint(0, i)
        arr[i], arr[j] = arr[j], arr[i]
    return arr


res = {}

for _ in range(100000):
    arr = [1, 2, 3]
    new_arr = shuffle(arr)
    keys = str(new_arr)
    res.setdefault(keys, 0)       
    res[keys] += 1

pprint(res)
