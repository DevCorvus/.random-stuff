import time
import heapq


def kth_largest_element(k, numbers):
    numbers = numbers.copy()

    for _ in range(k - 1):
        numbers.remove(max(numbers))

    return max(numbers)


def kth_largest_element_sorted(k, numbers):
    sorted_numbers = sorted(numbers)
    return sorted_numbers[len(sorted_numbers) - k]


def kth_largest_element_heap(k, numbers):
    numbers = [-number for number in numbers]
    heapq.heapify(numbers)

    for _ in range(k - 1):
        heapq.heappop(numbers)

    return -heapq.heappop(numbers)


k = 4  # 4th largest number
numbers = [4, 2, 9, 7, 5, 6, 7, 1, 3]

t = time.process_time()
print("Custom:", kth_largest_element(k, numbers))
print("took {:f} seconds\n".format(time.process_time() - t))

t = time.process_time()
print("Sorted:", kth_largest_element_sorted(k, numbers))
print("took {:f} seconds\n".format(time.process_time() - t))

t = time.process_time()
print("Heap:", kth_largest_element_heap(k, numbers))
print("took {:f} seconds\n".format(time.process_time() - t))
