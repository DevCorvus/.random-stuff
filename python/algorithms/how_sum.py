import time


def how_sum(amount, numbers):
    if amount == 0:
        return []

    if amount < 0:
        return None

    for number in numbers:
        remainder = amount - number
        remainder_result = how_sum(remainder, numbers)

        if remainder_result != None:
            remainder_result.append(number)
            return remainder_result

    return None


# It never hits the cache kekw
def how_sum_with_memo(amount, numbers, memo={}):
    if amount == 0:
        return []

    if amount < 0:
        return None

    if amount in memo:
        return memo[amount]

    for number in numbers:
        remainder = amount - number
        remainder_result = how_sum_with_memo(remainder, numbers, memo)

        if remainder_result != None:
            remainder_result.append(number)

            memo[amount] = remainder_result
            return remainder_result

    memo[amount] = None
    return None


amount = 5
numbers = [7, 3, 5, 2, 6, 11, 19]

t = time.process_time()
print("No Memo:", how_sum(amount, numbers))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", how_sum_with_memo(amount, numbers))
print("took {:f} seconds".format(time.process_time() - t))
