mod calculator;
mod cli;
mod conditionals_and_loops;
mod enums;
mod functions;
mod guess_game;
mod person;
mod pointers_ref;
mod print;
mod random;
mod structs;
mod types;
mod vars;

fn main() {
    println!("Learning the Rust Programming Language!");
    print::run();
    vars::run();
    types::run();
    conditionals_and_loops::run();
    functions::run();
    pointers_ref::run();
    structs::run();
    enums::run();
    cli::run();
    let result = calculator::run(4.0, 8.0);
    println!(
        "Add result: {} | Substract result: {} | Multiply result {} | Divide result {}",
        result.add, result.substract, result.multiply, result.divide
    );
    person::run();
    guess_game::run();
    random::run();
}
