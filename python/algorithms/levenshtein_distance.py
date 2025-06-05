from typing import List, TypedDict


# Wagner-Fischer Algorithm (Dynamic Programming)
def levenshtein_distance(s1: str, s2: str) -> int:
    s1_len = len(s1)
    s2_len = len(s2)

    matrix = [[0] * (s2_len + 1) for _ in range(s1_len + 1)]

    for i in range(s1_len + 1):
        matrix[i][0] = i
    for i in range(s2_len + 1):
        matrix[0][i] = i

    for i in range(1, s1_len + 1):
        for j in range(1, s2_len + 1):
            if s1[i - 1] == s2[j - 1]:
                cost = 0
            else:
                cost = 1

            matrix[i][j] = min(
                matrix[i - 1][j] + 1,  # Deletion
                matrix[i][j - 1] + 1,  # Insertion
                matrix[i - 1][j - 1] + cost,  # Substitution
            )

    return matrix[s1_len][s2_len]


my_input = input("Input: ")
my_dict = ["apple", "banana", "orange", "watermelon", "piña"]


class Guess(TypedDict):
    word: str
    distance: int


results: List[Guess] = []

for word in my_dict:
    distance = levenshtein_distance(my_input, word)
    results.append({"word": word, "distance": distance})

results.sort(key=lambda guess: guess["distance"])

for guess in results:
    print(guess)
