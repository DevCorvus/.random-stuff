def is_palindrome(word) -> bool:
    word_length = len(word)

    if word_length <= 1:
        return True

    if word[0] == word[word_length - 1]:
        return is_palindrome(word[1 : word_length - 1])

    return False


word = "ojo rojo"

print(is_palindrome("".join(word.split(" "))))
