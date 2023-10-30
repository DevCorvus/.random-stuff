#! /bin/bash

fruits=()

print_fruits()
{
  for fruit in "${fruits[@]}"; do
    echo "So you like: $fruit"
  done
}

while [ true ]
do
  echo "Enter a fruit:"
  read fruit

  fruits+=("$fruit")

  print_fruits $fruits
done