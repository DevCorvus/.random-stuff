import time


def count_change(amount, coins, coinIndex=0):
    if amount == 0:
        return 1

    if coinIndex >= len(coins):
        return 0

    value = coins[coinIndex]

    total_ways = 0

    qty = 0
    while qty * value <= amount:
        sub_amount = amount - (qty * value)
        total_ways += count_change(sub_amount, coins, coinIndex + 1)

        qty += 1

    return total_ways


def count_change_with_memo(amount, coins, coinIndex=0, memo={}):
    if amount == 0:
        return 1

    if coinIndex >= len(coins):
        return 0

    key = f"{amount}:{coinIndex}"

    if memo.get(key):
        return memo[key]

    total_ways = 0
    value = coins[coinIndex]

    qty = 0
    while qty * value <= amount:
        sub_amount = amount - (qty * value)
        total_ways += count_change_with_memo(sub_amount, coins, coinIndex + 1, memo)

        qty += 1

    memo[key] = total_ways
    return total_ways


amount = 4
coins = [1, 2, 3]

t = time.process_time()
print("No Memo:", count_change(amount, coins))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", count_change_with_memo(amount, coins, memo={}))
print("took {:f} seconds".format(time.process_time() - t))
