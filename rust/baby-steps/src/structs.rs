// Traditional Struct
struct Color {
  red: u8,
  green: u8,
  blue: u8
}
// Tuple Struct
struct Point(i32, i32);

struct Person {
  first_name: String,
  last_name: String
}

impl Person {
  // Costruct Person
  fn new(first: &str, last: &str) -> Person {
    Person {
      first_name: first.to_string(),
      last_name: last.to_string()
    }
  }
  // Get full name
  fn full_name(&self) -> String {
    format!("{} {}", self.first_name, self.last_name)
  }
  // Set last name
  fn set_last_name(&mut self, last: &str) {
    self.last_name = last.to_string();
  }

  // Name to tuple
  fn to_tuple(self) -> (String, String) {
    (self.first_name, self.last_name)
  }
}

pub fn run() {
  let mut my_color = Color {
    red: 255,
    green: 0,
    blue: 0
  };
  my_color.green = 125;
  println!("Color: {} {} {}", my_color.red, my_color.green, my_color.blue);

  let mut my_point = Point(44, 69);
  my_point.0 = 4;
  println!("Point: {} {}", my_point.0, my_point.1);

  let mut person = Person::new("Corvus", "Portillo");
  person.set_last_name("Luis");
  println!("Person: {} {}", person.first_name, person.last_name);
  println!("Person: {}", person.full_name());
  println!("Person like Tuple: {:?}", person.to_tuple());
}