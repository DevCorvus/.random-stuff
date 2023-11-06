# Like count_paths


def grid_traveler(y, x):
    if y == 0 or x == 0:
        return 0

    if y == 1 or x == 1:
        return 1

    grid = []
    for _ in range(y + 1):
        row = []
        for _ in range(x + 1):
            row.append(0)

        grid.append(row)

    grid[1][1] = 1

    for i in range(y + 1):
        for j in range(x + 1):
            curr = grid[i][j]

            if (i + 1) <= y:
                grid[i + 1][j] += curr

            if (j + 1) <= x:
                grid[i][j + 1] += curr

    # Debug
    for row in grid:
        print(row)

    return grid[y][x]


print(grid_traveler(3, 3))
