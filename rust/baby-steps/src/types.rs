/*
Primitive Types:

Integers: u8, i8, u16, i16, u32, i32, u64, i64, u128, i128 (Number of bits in memory)
Floats: f32, f64
Boolean: bool
Characters: char
Tuples
Arrays
*/

// Rust infers a lot of types like TypeScript

use std::mem;

pub fn run() {
    let x = 1; // By default this is i32
    let y = 2.5; // By default this is f64

    //Explicit Type
    let z: u8 = 1;

    // Find max size
    println!("Max i32: {}", std::i32::MAX);
    println!("Max i64: {}", std::i64::MAX);

    // Boolean
    let positive = true;
    let negative = false;

    // Get boolean by expression
    let is_equal_to_sublime = 4 == 4;

    // Char
    let gender = 'M';
    let face = '\u{1F600}';

    println!(
        "{:?}",
        (
            x,
            y,
            z,
            positive,
            negative,
            is_equal_to_sublime,
            gender,
            face
        )
    );

    // Primitive str: Immutable fixed-length string in memory

    // String: Growable, heap-allocated data structure (mutable)
    let mut hello = String::from("Hello");
    hello.push(' '); // Push char
    hello.push_str("World"); // Push string

    println!("{}, Length: {}", hello, hello.len()); // Also getting the length

    // Capacity in Bytes
    println!("Capacity: {}", hello.capacity());

    // Other Methods
    println!("Is Empty: {}", hello.is_empty());
    println!("Contains 'World': {}", hello.contains("World"));
    println!("Replace: {}", hello.replace("World", "Rust"));

    // Loop through string by whitespace
    for word in hello.split_whitespace() {
        println!("{}", word);
    }

    // Create string with capacity
    let mut s = String::with_capacity(10);
    s.push('S');
    s.push('P');

    // Assertion testing
    assert_eq!(2, s.len());
    assert_eq!(10, s.capacity());

    // Tuples
    let person: (&str, &str, u8) = ("Luis", "Portillo", 19);
    let (first_name, last_name, age) = person;
    println!("{} {} is {}", person.0, person.1, person.2);
    println!("{} {} is {}", first_name, last_name, age);

    // Arrays
    let mut names: [&str; 4] = ["Luis", "Fulano", "Fulana", "Maricarmen"];
    println!("{:?}", names);
    // Get single value
    names[0] = "Corvus"; // Re-asign values
    println!(
        "Single value in 'names': {}, length: {}",
        names[0],
        names.len()
    ); // Also getting the length
       // Arrays are stack allocated
    println!("Arrays occupies {} bytes", mem::size_of_val(&names));
    // Slice array
    let numbers: [i32; 4] = [1, 2, 3, 4];
    let numbers = [4; 4]; // Four Fours in the Array. Using shadowing
    let slice: &[i32] = &numbers[2..4];
    println!("{:?}", slice);

    // Vectors (Resizable arrays)
    let mut numbers_list: Vec<i32> = vec![1, 2, 3, 4];
    // It has most of the methods like an array
    numbers_list.push(5);
    numbers_list.push(6);
    // Pop off last value
    numbers_list.pop();
    numbers_list.pop();

    // Loop through vectors
    for x in numbers_list.iter() {
        println!("Number: {}", x);
    }
    // Loop and mutate vectors
    for x in numbers_list.iter_mut() {
        *x *= 2;
    }
    println!("Numbers duplicated: {:?}", numbers_list);
}
