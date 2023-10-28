def remainder(dividend, divisor):
    division = dividend / divisor

    rounded_division = round(division)

    rounded_division_times_divisor = rounded_division * divisor

    return dividend - rounded_division_times_divisor
