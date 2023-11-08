from copy import deepcopy
import time


def best_sum(amount, numbers):
    if amount == 0:
        return []

    if amount < 0:
        return None

    shortest_combination = None

    for number in numbers:
        remainder = amount - number
        remainder_combination = best_sum(remainder, numbers)

        if remainder_combination != None:
            remainder_combination.append(number)

            if not shortest_combination or len(remainder_combination) < len(
                shortest_combination
            ):
                shortest_combination = remainder_combination

    return shortest_combination


def best_sum_with_memo(amount, numbers, memo={}):
    if amount == 0:
        return []

    if amount < 0:
        return None

    if amount in memo:
        return memo[amount]

    shortest_combination = None

    for number in numbers:
        remainder = amount - number
        remainder_combination = best_sum_with_memo(remainder, numbers, memo)

        if remainder_combination != None:
            remainder_combination = deepcopy(remainder_combination + [number])

            if not shortest_combination or len(remainder_combination) < len(
                shortest_combination
            ):
                shortest_combination = remainder_combination

    memo[amount] = shortest_combination
    return shortest_combination


def best_sum_tabulation(amount, numbers):
    table = []
    for _ in range(amount + 1):
        table.append(None)

    table[0] = []

    for i in range(amount):
        if table[i] != None:
            for number in numbers:
                if (i + number) <= amount:
                    combination = table[i] + [number]
                    if table[i + number] == None or len(combination) < len(
                        table[i + number]
                    ):
                        table[i + number] = combination

    return table[amount]


amount = 30
numbers = [1, 2, 5]

t = time.process_time()
print("No Memo:", best_sum(amount, numbers))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", best_sum_with_memo(amount, numbers))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Tabulation:", best_sum_tabulation(amount, numbers))
print("took {:f} seconds".format(time.process_time() - t))
