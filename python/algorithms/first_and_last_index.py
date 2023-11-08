# Get first and last index of consecutive target in sorted numbers


def first_and_last_index(target, sorted_integers):
    sorted_integers_len = len(sorted_integers)

    try:
        start_index = sorted_integers.index(target)
        end_index = start_index

        while (
            start_index <= sorted_integers_len
            and sorted_integers[end_index + 1] == target
        ):
            end_index += 1

        return [start_index, end_index]

    except:
        return [-1, -1]


target = 5
sorted_integers = [2, 4, 5, 5, 5, 7, 9, 9]

print(first_and_last_index(target, sorted_integers))
