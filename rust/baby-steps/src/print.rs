pub fn run() {
    // Print to Console
    println!("Hello from the print.rs file!");
    // Basic Formatting
    println!("Number is: {}", 1);
    println!("I'm {} and I will be {}", "Luis", "BANANAS");
    // Positional Arguments
    println!(
        "{0} is an idiot because {0} thinks that he can {1} how to code in {2}",
        "Luis", "learn", "Rust"
    );
    // Named Arguments
    println!(
        "{name} likes to learn {thing}",
        name = "Luis",
        thing = "new Programming Languages"
    );
    // Placeholder Traits
    println!("Binary: {:b} Hex: {:x} Octal: {:o}", 10, 10, 10);
    // Placeholder for debug trait
    println!("{:?}", (12, true, "Hello"));
    //Basic Math
    println!("Your result is: {}", 2 + 2);
}
