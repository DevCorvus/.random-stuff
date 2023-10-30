pub fn run() {
  let name = "Luis";
  let mut age = 69;
  println!("My name is {} and I am {} years old", name, age);
  age = 19;
  println!("My name is {} and I am {} years old", name, age);

  //Define Constant
  const ID: i32 = 4;
  println!("The ID is {}", ID);

  // Multiple variables at once
  let (country, gender) = ("Venezuela", "Male");
  println!(
    "{} is a {} that came from {}",
    name, gender, country
  );
}