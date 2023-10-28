import math


def to_binary(decimal, result=""):
    if decimal == 0:
        return result

    remainder = decimal % 2
    result = f"{remainder}{result}"
    return to_binary(math.floor(decimal / 2), result)


print(to_binary(7))
