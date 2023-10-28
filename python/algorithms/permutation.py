import math


def permutation(lst):
    lst_len = len(lst)

    if lst_len == 0:
        return []
    elif lst_len == 1:
        return [lst]

    current_permutation = []

    for i in range(lst_len):
        el = lst[i]

        remaining_list = lst[:i] + lst[i + 1 :]

        for p in permutation(remaining_list):
            current_permutation.append([el] + p)

    return current_permutation


def backtrack_permutation(a, l, r):
    if l == r:
        print("".join(a))
    else:
        for i in range(l, r):
            a[l], a[i] = a[i], a[l]
            backtrack_permutation(a, l + 1, r)
            a[l], a[i] = a[i], a[l]


letters = list("ABC")

result = permutation(letters)
print(result)

backtrack_permutation(letters, 0, len(letters))

possible_permutations = math.factorial(len(letters))  # 1 * 2 * 3
possible_permutations_with_repetition = math.pow(
    len(letters), len(letters)
)  # N raised to the power of N

print(possible_permutations, possible_permutations_with_repetition)
