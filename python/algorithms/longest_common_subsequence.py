import time


def lcs(s1, s2, m, n):
    if m == 0 or n == 0:
        return 0
    elif s1[m - 1] == s2[n - 1]:
        return 1 + lcs(s1, s2, m - 1, n - 1)
    else:
        return max(lcs(s1, s2, m, n - 1), lcs(s1, s2, m - 1, n))


def lcs_with_memo(s1, s2, m, n, memo):
    if m == 0 or n == 0:
        return 0

    if memo[m][n] != -1:
        return memo[m][n]

    if s1[m - 1] == s2[n - 1]:
        memo[m][n] = 1 + lcs_with_memo(s1, s2, m - 1, n - 1, memo)
        return memo[m][n]

    memo[m][n] = max(
        lcs_with_memo(s1, s2, m, n - 1, memo), lcs_with_memo(s1, s2, m - 1, n, memo)
    )
    return memo[m][n]


def lcs_tabulation(s1, s2):
    m = len(s1)
    n = len(s2)
    table = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(m + 1):
        for j in range(n + 1):
            if s1[i - 1] == s2[j - 1]:
                table[i][j] = 1 + table[i - 1][j - 1]
            else:
                table[i][j] = max(table[i - 1][j], table[i][j - 1])

    return table[m][n]


def lcs_tabulation_optimized(s1, s2):
    n = len(s1)
    m = len(s2)

    prev = [0] * (m + 1)
    curr = [0] * (m + 1)

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if s1[i - 1] == s2[j - 1]:
                curr[j] = 1 + prev[j - 1]
            else:
                curr[j] = max(curr[j - 1], prev[j])

        prev = curr.copy()

    return curr[m]


s1 = "banana"
s2 = "analize"
m = len(s1)
n = len(s2)
memo = [[-1] * (n + 1) for _ in range(m + 1)]

t = time.process_time()
print("No Memo:", lcs(s1, s2, m, n))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", lcs_with_memo(s1, s2, m, n, memo))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Tabulation:", lcs_tabulation(s1, s2))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Tabulation (Optimized):", lcs_tabulation_optimized(s1, s2))
print("took {:f} seconds".format(time.process_time() - t))
