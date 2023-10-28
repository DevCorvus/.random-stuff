def power(n, r):
    value = n

    if r > 0:
        for _ in range(r - 1):
            value *= n

        return value
    else:
        for _ in range(abs(r) - 1):
            value *= n

        return 1 / value
