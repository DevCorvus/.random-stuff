def arrange(arr):
    out = arr.copy()

    while True:
        action = False

        for i, n in enumerate(out):
            if i == len(out) - 1:
                break

            if n > out[i + 1]:
                out[i] = out[i + 1]
                out[i + 1] = n
                action = True

        if not action:
            break

    return out


def sum_all(arr):
    out = 0

    for n in arr:
        out += n

    return out


def get_mean(arr):
    total = sum_all(arr)
    length = len(arr)

    return total / length


def get_median(arr):
    length = len(arr)
    center = length / 2

    arranged_list = arrange(arr)

    if length % 3 == 0:
        return arranged_list[center]
    else:
        idx = int(center)

        n1 = arranged_list[idx - 1]
        n2 = arranged_list[idx]

        return (n1 + n2) / 2


def get_mode(arr):
    out = []

    for n in arr:
        if arr.count(n) > 1 and not out.count(n) > 0:
            out.append(n)

    return out


def get_range(arr):
    length = len(arr)
    arranged_list = arrange(arr)

    last = arranged_list[length - 1]
    first = arranged_list[0]

    return last - first


numbers = [15, 21, 59, 15, 37, 59, 11, 41]

print(get_mean(numbers), get_median(numbers), get_mode(numbers), get_range(numbers))
