def logarithm(n, b=2):
    current_value = 1

    for i in range(1, n):
        result = current_value * b

        if result == n:
            return i + 1
        else:
            current_value = result

    return 0


print(logarithm(32))
