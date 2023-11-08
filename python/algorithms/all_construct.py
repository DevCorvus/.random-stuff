import time
from copy import deepcopy


def all_construct(target_word, word_bank):
    if target_word == "":
        return [[]]

    possible_combinations = []
    for word in word_bank:
        if target_word.startswith(word):
            target_word_suffix = target_word[len(word) :]
            sub_possible_combinations = all_construct(target_word_suffix, word_bank)

            for combination in sub_possible_combinations:
                combination.insert(0, word)

            possible_combinations += sub_possible_combinations

    return possible_combinations


def all_construct_with_memo(target_word, word_bank, memo={}):
    if target_word == "":
        return [[]]

    if target_word in memo:
        return memo[target_word]

    possible_combinations = []
    for word in word_bank:
        if target_word.startswith(word):
            target_word_suffix = target_word[len(word) :]
            sub_possible_combinations = all_construct_with_memo(
                target_word_suffix, word_bank, memo
            )

            for combination in sub_possible_combinations:
                combination.insert(0, word)

            possible_combinations += sub_possible_combinations

    memo[target_word] = deepcopy(possible_combinations)
    return possible_combinations


def all_construct_tabulation(target_word, word_bank):
    target_word_len = len(target_word)

    table = [[] for _ in range(target_word_len + 1)]

    table[0] = [[]]

    for i in range(target_word_len):
        for word in word_bank:
            word_len = len(word)

            if target_word[i : i + word_len] == word:
                combinations = [combination + [word] for combination in table[i]]
                table[i + word_len] += combinations

    return table[target_word_len]


target_word = "fulano"
word_bank = ["f", "u", "l", "fu", "ful", "ano"]


t = time.process_time()
print("No Memo:", all_construct(target_word, word_bank))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", all_construct_with_memo(target_word, word_bank))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Tabulation:", all_construct_tabulation(target_word, word_bank))
print("took {:f} seconds".format(time.process_time() - t))
