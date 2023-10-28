import time


def min_change(amount, coins):
    if amount == 0:
        return 0

    if amount < 0:
        return -1

    min_coins = -1
    for coin in coins:
        sub_min_coins = min_change(amount - coin, coins)

        if sub_min_coins != -1:
            num_coins = sub_min_coins + 1

            if num_coins < min_coins or min_coins == -1:
                min_coins = num_coins

    return min_coins


def min_change_with_memo(amount, coins, memo):
    if amount == 0:
        return 0

    if amount < 0:
        return -1

    if memo.get(amount):
        return memo[amount]

    min_coins = -1
    for coin in coins:
        sub_coins = min_change_with_memo(amount - coin, coins, memo)

        if sub_coins != -1:
            num_coins = sub_coins + 1

            if num_coins < min_coins or min_coins == -1:
                min_coins = num_coins

    memo[amount] = min_coins
    return min_coins


amount = 5
coins = [2, 3]

t = time.process_time()
print("No Memo:", min_change(amount, coins))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", min_change_with_memo(amount, coins, {}))
print("took {:f} seconds".format(time.process_time() - t))
