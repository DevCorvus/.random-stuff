import time
from collections import Counter


def get_chars_freq(text):
    freq_table = {}

    for c in text:
        if c in freq_table:
            freq_table[c] += 1
        else:
            freq_table[c] = 1

    return freq_table


def are_anagrams(s1, s2):
    if len(s1) != len(s2):
        return False

    return get_chars_freq(s1) == get_chars_freq(s2)


def are_anagrams_native_counter(s1, s2):
    if len(s1) != len(s2):
        return False

    return Counter(s1) == Counter(s2)


def are_anagrams_sorted(s1, s2):
    if len(s1) != len(s2):
        return False

    return sorted(s1) == sorted(s2)


s1 = "a gentleman"
s2 = "elegant man"

t = time.process_time()
print("Custom:", are_anagrams(s1, s2))
print("took {:f} seconds\n".format(time.process_time() - t))

t = time.process_time()
print("Native Counter:", are_anagrams_native_counter(s1, s2))
print("took {:f} seconds\n".format(time.process_time() - t))

t = time.process_time()
print("Sorted:", are_anagrams_sorted(s1, s2))
print("took {:f} seconds\n".format(time.process_time() - t))
