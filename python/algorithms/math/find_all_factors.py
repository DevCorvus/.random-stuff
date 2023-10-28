from modulus import remainder

# O(n) linear time complexity
def find_all_factors(n):
    half = round(n / 2) + 1

    factors = [1]  # 1 is always a factor

    for i in range(2, half):
        if remainder(n, i) == 0:
            factors.append(i)

    factors.append(n)

    return factors
