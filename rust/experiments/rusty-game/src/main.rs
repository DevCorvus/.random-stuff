use console::{Key, Term};

use rusty_game::core::{Direction, Game, GameGrid, Move, Square, SquareType};
use rusty_game::utils::get_boundaries;

fn main() {
    let stdout = Term::stdout();

    let grid_boundaries = get_boundaries(&stdout).unwrap();

    let game_grid: GameGrid =
        vec![vec![Square::new(SquareType::Empty); grid_boundaries.x]; grid_boundaries.y];

    let mut game = Game {
        grid: game_grid,
        boundaries: grid_boundaries,
    };

    game.generate_obstacles(10);
    let mut last_position = game.spawn_player();

    stdout.clear_screen().unwrap();
    game.render_grid();

    loop {
        if let Ok(key) = stdout.read_key() {
            let direction = match key {
                Key::Char('w') | Key::ArrowUp => Direction::Up,
                Key::Char('a') | Key::ArrowLeft => Direction::Left,
                Key::Char('s') | Key::ArrowDown => Direction::Down,
                Key::Char('d') | Key::ArrowRight => Direction::Right,
                _ => break,
            };

            last_position = game.move_entity(Move {
                direction,
                position: last_position,
            });
        }
        stdout.clear_screen().unwrap();
        game.render_grid();
    }
}
