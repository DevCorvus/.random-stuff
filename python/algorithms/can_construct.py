import time


def can_construct(target_word, word_bank):
    if target_word == "":
        return True

    for word in word_bank:
        if target_word.startswith(word):
            target_word_suffix = target_word[len(word) :]
            if can_construct(target_word_suffix, word_bank):
                return True

    return False


def can_construct_with_memo(target_word, word_bank, memo={}):
    if target_word == "":
        return True

    if target_word in memo:
        return memo[target_word]

    for word in word_bank:
        if target_word.startswith(word):
            target_word_suffix = target_word[len(word) :]
            if can_construct_with_memo(target_word_suffix, word_bank, memo):
                memo[target_word] = True
                return True

    memo[target_word] = False
    return False


target_word = "fulano"
word_bank = ["f", "u", "fu", "ful", "ano"]


t = time.process_time()
print("No Memo:", can_construct(target_word, word_bank))
print("took {:f} seconds".format(time.process_time() - t))

t = time.process_time()
print("Memoized:", can_construct_with_memo(target_word, word_bank))
print("took {:f} seconds".format(time.process_time() - t))
