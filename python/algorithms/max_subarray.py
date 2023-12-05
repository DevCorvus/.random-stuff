import time


def max_subarray(numbers):
    numbers_len = len(numbers)
    max_subarray_sum = None

    # start = 0
    # end = 0

    for i in range(numbers_len):
        curr_sum = 0

        for j in range(i, numbers_len):
            curr_sum += numbers[j]

            if max_subarray_sum is None or curr_sum > max_subarray_sum:
                max_subarray_sum = curr_sum
                # start = i
                # end = j

    # return (max_subarray_sum, [start, end])
    return max_subarray_sum


def max_subarray_dp(numbers):
    max_so_far = numbers[0]
    max_ending_here = numbers[0]

    for number in numbers:
        max_ending_here = max(number, max_ending_here + number)

        if max_so_far < max_ending_here:
            max_so_far = max_ending_here

    return max_so_far


numbers = [-3, 1, -8, 4, -1, 2, 1, -5, 5]

t = time.process_time()
print("Brute force:", max_subarray(numbers))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Optimized:", max_subarray_dp(numbers))
print("took {:f} seconds".format(time.process_time() - t))
