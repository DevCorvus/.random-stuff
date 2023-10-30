use std::env::{args, Args};

fn main() {
    let mut args: Args = args();
    let first_arg = args.nth(1).unwrap();
    let operator = args.nth(0).unwrap().chars().next().unwrap();
    let second_arg = args.nth(0).unwrap();

    let first_number = first_arg.parse::<f32>().unwrap();
    let second_number = second_arg.parse::<f32>().unwrap();

    let result: f32 = operate(operator, first_number, second_number);

    println!("{}", output(first_number, operator, second_number, result));
}

fn operate(operator: char, number1: f32, number2: f32) -> f32 {
    match operator {
        '+' => number1 + number2,
        '-' => number1 - number2,
        '/' => number1 / number2,
        '*' | 'x' | 'X' => number1 * number2,
        _ => panic!("Invalid operator"),
    }
}

fn output(number1: f32, operator: char, number2: f32, result: f32) -> String {
    format!("{} {} {} = {}", number1, operator, number2, result)
}
