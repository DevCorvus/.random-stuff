import time
from typing import List


def sum_possible(amount: int, numbers: List[int]) -> bool:
    if amount == 0:
        return True

    if amount < 0:
        return False

    for n in numbers:
        if sum_possible(amount - n, numbers):
            return True

    return False


def sum_possible_with_memo(amount: int, numbers: List[int], memo) -> bool:
    if amount == 0:
        return True

    if amount < 0:
        return False

    if memo.get(amount):
        return memo[amount]

    for n in numbers:
        if sum_possible_with_memo(amount - n, numbers, memo):
            memo[amount] = True
            return True

    memo[amount] = False
    return False


def sum_possible_tabulation(amount: int, numbers: List[int]) -> bool:
    table = [False] * (amount + 1)

    table[0] = True

    for i in range(amount):
        if table[i] == True:
            for number in numbers:
                if (i + number) <= amount:
                    table[i + number] = True

    return table[amount]


amount = 5
numbers = [2, 3]

t = time.process_time()
print("No Memo:", sum_possible(amount, numbers))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", sum_possible_with_memo(amount, numbers, {}))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Tabulation:", sum_possible_tabulation(amount, numbers))
print("took {:f} seconds".format(time.process_time() - t))
