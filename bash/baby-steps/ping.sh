#! /bin/bash

# GET THE PING AVERAGE
# ping google.com four times |
# get the last line |
# select the fourth section (separated with space) |
# cut that section for each '/' and select the second field
# cut the decimal part and only get the integer

# avg=$(ping google.com -c 4 | tail -1 | awk '{print $4}' | cut -d '/' -f 2 | cut -d '.' -f 1)

count=4

ms_list=$(ping google.com -c $count | grep time= | awk '{print $8}' | cut -d '=' -f 2 | cut -d '.' -f 1)

sum=0

for ms in ${ms_list[@]}; do
  let sum+=$ms
done

# avg=$(($sum / $count))
# avg=$(expr $sum / $count)
let "avg = $sum / $count"

if [[ "$avg" -le 50 ]]; then
  echo "You're good to go!"
else
  echo "You're not good to go .c"
fi