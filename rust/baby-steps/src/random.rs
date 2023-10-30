struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }

    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}

struct Color(i32, i32, i32);

// enum IpAddrKind {
//   V4,
//   V6
// }

// struct IpAddr {
//   kind: IpAddrKind,
//   address: String
// }

enum IpAddr {
    // V4(String),
    V4(u8, u8, u8, u8),
    V6(String),
}

enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn call(&self) {
        println!("Calling Message Enum Method.");
    }
}

pub fn run() {
    let mut counter = 0;

    let result = loop {
        counter += 1;

        if counter == 10 {
            break counter * 2;
        }
    };

    println!("Counter: {}", result);

    // FACTS ABOUT RUST

    let s1 = String::from("hello");
    let s2 = s1; // The reference of s1 in the heap has moved to s2, so s1 is no longer available.
    let s3 = String::from("bye");
    let s4 = s3.clone(); // Deep Copy
                         // This behavior it's only for memory allocated in the Heap, so an integer would be deeply copied wihout the clone method.
                         // Passing arguments to functions will also trigger this behavior.
                         // It's all about the concept of "Ownership" in Rust.
                         // Functions can move Ownerships when they return, we can prevent this with references "&" which are inmutable by default but we can change it with "&mut".
                         // We can't create inmutable references twice an also cannot combine inmutable and mutable references because overlap.
                         // Rere

    // END OF FACTS

    for number in (1..4).rev() {
        println!("{}!", number);
    }
    println!("LIFTOFF!!!");

    let mut text = String::from("Hello");
    text.push_str(" World");
    let word: &str = first_word(&text);
    println!("First Word: {}", word);

    let color1: Color = Color(255, 0, 0);
    println!("Red: {} Green: {} Blue: {}", color1.0, color1.1, color1.2);

    let rect1: Rectangle = Rectangle {
        width: 50,
        height: 30,
    };

    let rect2: Rectangle = Rectangle {
        width: 60,
        height: 40,
    };

    println!("Rectangle Area: {}", rect1.area());
    println!("Can Hold? {}", rect1.can_hold(&rect2));
    println!("Rectangle Area: {}", rect2.area());
    println!("Can Hold? {}", rect2.can_hold(&rect1));

    // let home = IpAddr {
    //   kind: IpAddrKind::V4,
    //   address: String::from("127.0.0.1")
    // };

    // let loopback = IpAddr {
    //   kind: IpAddrKind::V6,
    //   address: String::from("::1")
    // };

    // let home = IpAddr::V4(String::from("127.0.0.1"));
    let _home = IpAddr::V4(127, 0, 0, 1);
    let _loopback = IpAddr::V6(String::from("::1"));

    let message = Message::Write(String::from("Programming"));
    message.call();
}

// fn first_word(text: &String) -> &str {
fn first_word(text: &str) -> &str {
    let bytes = text.as_bytes();

    for (i, &letter) in bytes.iter().enumerate() {
        println!("i: {} letter_reference: {}", i, &letter);
        if letter == b' ' {
            return &text[..i];
        }
    }
    &text[..]
}
