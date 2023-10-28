def count_partitions(a, b):
    if a == 0:
        return 1
    if b == 0 or a < 0:
        return 0

    return count_partitions(a - b, b) + count_partitions(a, b - 1)


print(count_partitions(7, 4))
