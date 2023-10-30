enum Movement {
    // Variants
    Up,
    Down,
    Left,
    Right,
}

fn move_avatar(m: Movement) {
    // Performing actions
    match m {
        Movement::Up => println!("Avatar moves up"),
        Movement::Down => println!("Avatar moves down"),
        Movement::Left => println!("Avatar moves left"),
        Movement::Right => println!("Avatar moves right"),
    }
}

pub fn run() {
    let avatar1 = Movement::Up;
    let avatar2 = Movement::Down;
    let avatar3 = Movement::Left;
    let avatar4 = Movement::Right;

    move_avatar(avatar1);
    move_avatar(avatar2);
    move_avatar(avatar3);
    move_avatar(avatar4);
}
