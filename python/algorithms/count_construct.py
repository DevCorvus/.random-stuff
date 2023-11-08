import time


def count_construct(target_word, word_bank):
    if target_word == "":
        return 1

    count = 0
    for word in word_bank:
        if target_word.startswith(word):
            target_word_suffix = target_word[len(word) :]
            count += count_construct(target_word_suffix, word_bank)

    return count


def count_construct_with_memo(target_word, word_bank, memo={}):
    if target_word == "":
        return 1

    if target_word in memo:
        return memo[target_word]

    count = 0
    for word in word_bank:
        if target_word.startswith(word):
            target_word_suffix = target_word[len(word) :]
            count += count_construct_with_memo(target_word_suffix, word_bank, memo)

    memo[target_word] = count
    return count


def count_construct_tabulation(target_word, word_bank):
    target_word_len = len(target_word)

    table = [0] * (target_word_len + 1)

    table[0] = 1

    for i in range(target_word_len):
        if table[i] != 0:
            for word in word_bank:
                word_len = len(word)

                if target_word[i : i + word_len] == word:
                    table[i + word_len] += table[i]

    return table[target_word_len]


target_word = "fulano"
word_bank = ["f", "u", "l", "fu", "ful", "ano"]


t = time.process_time()
print("No Memo:", count_construct(target_word, word_bank))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", count_construct_with_memo(target_word, word_bank))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Tabulation:", count_construct_tabulation(target_word, word_bank))
print("took {:f} seconds".format(time.process_time() - t))
