fruits = ["banana", "watermelon", "apple", "strawberry"]

for fruit <- fruits, do: IO.puts(fruit)

values = [good: 1, good: 2, bad: 3, good: 4]
for {:good, n} <- values, do: n * n
