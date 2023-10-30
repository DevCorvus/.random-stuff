pub fn run() {
    const ADULT_AGE: u8 = 18;

    let age = 19;
    let check_id = true;
    let my_son = true;

    if age >= ADULT_AGE && check_id || my_son {
        println!("You can pass");
    } else if age < ADULT_AGE && check_id {
        println!("You have your ID but you cannot pass");
    } else {
        println!("You shall not pass");
    }
    // Shorthand
    let is_adult = if age >= 18 { true } else { false };
    println!("Is adult: {}", is_adult);

    let mut count = 10;
    // Infinite loop
    loop {
        println!("Number: {}", count);
        count -= 1;
        if count == 1 {
            break;
        }
    }
    // While loop
    while count <= 15 {
        if count % 15 == 0 {
            println!("fizzbuzz");
        } else if count % 3 == 0 {
            println!("fizz");
        } else if count % 5 == 0 {
            println!("buzz");
        } else {
            println!("{}", count);
        }
        count += 1;
    }

    // For Range
    for x in 1..5 {
        if x == 4 {
            println!("Number: SUBLIME");
        } else {
            println!("Number: {}", x);
        }
    }
}
