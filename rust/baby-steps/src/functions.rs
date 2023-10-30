pub fn run() {
    greeting("Luis");

    let get_sum = add(69, 4);
    println!("Result: {}", get_sum);

    // Closure
    let constant_value = 4;
    let add_nums = |n1: i32, n2: i32| n1 + n2 + constant_value;
    println!("Closure Sum Result: {}", add_nums(60, 9));
}

fn greeting(name: &str) {
    println!("Hi {}!", name);
}

fn add(n1: i32, n2: i32) -> i32 {
    n1 + n2 // If we don't set a semicolon it will be the return
}
