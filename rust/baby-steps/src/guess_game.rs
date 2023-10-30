use std::cmp::Ordering;
use std::io;

pub fn run() {
    println!("Guess the number!");
    println!("Please input your guess.");
    loop {
        let mut guess = String::new();
        let secret_number: u8 = 44;

        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line!");

        // let guess: u8 = guess.trim().parse().expect("Please type a number!");
        let guess: u8 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Please type a number!");
                continue;
            }
        };

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win! It was {}!", { secret_number });
                break;
            }
        };
    }
}
