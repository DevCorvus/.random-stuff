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


target_word = "fulano"
word_bank = ["f", "u", "l", "fu", "ful", "ano"]


t = time.process_time()
print("No Memo:", count_construct(target_word, word_bank))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", count_construct_with_memo(target_word, word_bank))
print("took {:f} seconds".format(time.process_time() - t))
