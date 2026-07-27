
from random import randint
from pprint import pprint

def shuffle (arr) :
    n = len(arr)
    for i in range(0, n):
        j = randint(i, n-1)
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

