from factorial import factorial
from exponential import power


def combination_without_repetition(n, r):
    n_factorial = factorial(n)

    n_minus_r_factorial = factorial(n - r)
    r_factorial = factorial(r)

    n_minus_r_factorial_times_r_factorial = n_minus_r_factorial * r_factorial

    return n_factorial / n_minus_r_factorial_times_r_factorial


def combination_with_repetition(n, r):
    n_plus_r_minus_one = (n + r) - 1
    n_plus_r_minus_one_factorial = factorial(n_plus_r_minus_one)

    n_minus_one_factorial = factorial(n - 1)
    r_factorial = factorial(r)
    n_minus_one_factorial_times_r_factorial = n_minus_one_factorial * r_factorial

    return n_plus_r_minus_one_factorial / n_minus_one_factorial_times_r_factorial


def permutation_without_repetition(n, r):
    n_factorial = factorial(n)

    n_minus_r_factorial = factorial(n - r)

    return n_factorial / n_minus_r_factorial


def permutation_with_repetition(n, r):
    return power(n, r)
