struct Person {
    fname: String,
    lname: String,
    age: u8,
    gender: char,
}

impl Person {
    fn new(fname: &str, lname: &str, age: u8, gender: char) -> Person {
        Person {
            fname: fname.to_string(),
            lname: lname.to_string(),
            age,
            gender,
        }
    }
    fn about(&self) -> String {
        let gender: &str;
        if self.gender == 'M' {
            gender = "man";
        } else {
            gender = "woman";
        }
        return format!(
            "My name is {fname} {lname} and I'm a {age} years old {gender}.",
            fname = self.fname,
            lname = self.lname,
            age = self.age,
            gender = gender
        );
    }
}

pub fn run() {
    let person = Person::new("Luis", "Portillo", 19, 'M');

    println!("{}", person.about());
}
