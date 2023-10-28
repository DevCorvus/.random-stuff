def sum_natural_numbers(n):
    if n <= 1:
        return n

    return n + sum_natural_numbers(n - 1)


print(sum_natural_numbers(10))
