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

    if memo.get(amount):
        return memo[amount]

    shortest_combination = None

    for number in numbers:
        remainder = amount - number
        remainder_combination = best_sum_with_memo(remainder, numbers, memo)

        if remainder_combination != None:
            remainder_combination.append(number)

            if not shortest_combination or len(remainder_combination) < len(
                shortest_combination
            ):
                shortest_combination = remainder_combination

    memo[amount] = shortest_combination
    return shortest_combination


amount = 30
numbers = [1, 2, 5, 30]

t = time.process_time()
print("No Memo:", best_sum(amount, numbers))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", best_sum_with_memo(amount, numbers))
print("took {:f} seconds".format(time.process_time() - t))
