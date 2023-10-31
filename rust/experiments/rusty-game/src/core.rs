use console::style;
use std::error::Error;

use rand::Rng;

use super::utils::to_fixed;

pub struct GridBoundaries {
    pub x: usize,
    pub y: usize,
}

impl GridBoundaries {
    fn is_out(&self, position: &Coordinate) -> bool {
        let x_out = position.x >= self.x;
        let y_out = position.y >= self.y;

        x_out || y_out
    }
}

pub type GameGrid = Vec<Vec<Square>>;

pub struct Game {
    pub grid: GameGrid,
    pub boundaries: GridBoundaries,
}

impl Game {
    pub fn render_grid(&self) {
        for row in &self.grid {
            print!("|");
            for square in row {
                print!(" ");
                if let Some(entity) = &square.entity {
                    print!("{}", style(entity.char).green());
                } else {
                    print!("{}", square.char);
                }
                print!(" ");
            }
            print!("|\n");
        }
    }

    fn select_square(&self, c: &Coordinate) -> &Square {
        &self.grid[c.y][c.x]
    }

    fn select_square_mut(&mut self, c: &Coordinate) -> &mut Square {
        &mut self.grid[c.y][c.x]
    }

    fn select_random_square_mut(&mut self) -> &mut Square {
        use rand::prelude::*;
        let selected_row = self.grid.choose_mut(&mut rand::thread_rng()).unwrap();
        let selected_square = selected_row.choose_mut(&mut rand::thread_rng()).unwrap();
        return selected_square;
    }

    fn select_random_coordinate(&self) -> Coordinate {
        let x = rand::thread_rng().gen_range(0..self.boundaries.x);
        let y = rand::thread_rng().gen_range(0..self.boundaries.y);
        return Coordinate { x, y };
    }

    pub fn generate_obstacles(&mut self, percentage: usize) {
        let grid_area = self.boundaries.x * self.boundaries.y;
        let fixed_percentage = to_fixed(percentage as f64 / 100.0, 2).unwrap();
        let amount = ((grid_area as f64) * fixed_percentage).round() as usize;

        for _ in 0..amount {
            loop {
                let square = self.select_random_square_mut();

                if square.get_type() == SquareType::Empty {
                    square.convert(SquareType::Obstacle);
                    break;
                }
            }
        }
    }

    pub fn spawn_player(&mut self) -> Coordinate {
        let player = Entity { char: 'P' };

        loop {
            let position = self.select_random_coordinate();
            let square = self.select_square_mut(&position);

            if square.passable {
                square.set_entity(player);
                return position;
            }
        }
    }

    fn get_next_position(
        &self,
        position: &Coordinate,
        direction: &Direction,
    ) -> Result<Coordinate, &str> {
        let mut next_position = Coordinate {
            x: position.x,
            y: position.y,
        };

        match direction {
            Direction::Up => {
                next_position.y = if next_position.y > 0 {
                    next_position.y - 1
                } else {
                    next_position.y
                }
            }
            Direction::Left => {
                next_position.x = if next_position.x > 0 {
                    next_position.x - 1
                } else {
                    next_position.x
                }
            }
            Direction::Down => next_position.y += 1,
            Direction::Right => next_position.x += 1,
        }

        if self.boundaries.is_out(&next_position) {
            Err("Out of boundaries")
        } else {
            Ok(next_position)
        }
    }

    fn swap_square(
        &mut self,
        position: &Coordinate,
        direction: &Direction,
    ) -> Result<(), Box<dyn Error>> {
        let next_position = self.get_next_position(position, direction)?;

        let prev_square_type = self.select_square(position).get_type();
        let next_square_type = self.select_square(&next_position).get_type();

        self.select_square_mut(position).convert(next_square_type);
        self.select_square_mut(&next_position)
            .convert(prev_square_type);

        Ok(())
    }

    fn push_squares(&mut self, position: &Coordinate, direction: &Direction) {
        let mut pushable_squares: Vec<Coordinate> = Vec::new();

        let mut current_position = Coordinate {
            x: position.x,
            y: position.y,
        };

        loop {
            if self.select_square(&current_position).pushable {
                pushable_squares.push(current_position.clone());

                if let Ok(next_position) = self.get_next_position(&current_position, direction) {
                    if !current_position.compare(&next_position) {
                        current_position = next_position;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                break;
            }
        }

        for c in pushable_squares.into_iter().rev() {
            let _ = self.swap_square(&c, direction);
        }
    }

    pub fn move_entity(&mut self, m: Move) -> Coordinate {
        let next_position: Coordinate;
        if let Ok(c) = self.get_next_position(&m.position, &m.direction) {
            next_position = c;
        } else {
            return m.position;
        }

        self.push_squares(&next_position, &m.direction);

        if self.select_square(&next_position).passable {
            let prev_entity = self.select_square_mut(&m.position).remove_entity().unwrap();

            self.select_square_mut(&next_position)
                .set_entity(prev_entity);

            return next_position;
        } else {
            return m.position;
        }
    }
}

pub enum Direction {
    Up,
    Left,
    Down,
    Right,
}

#[derive(Debug, Clone)]
pub struct Coordinate {
    pub x: usize,
    pub y: usize,
}

impl Coordinate {
    fn compare(&self, c: &Coordinate) -> bool {
        self.x == c.x && self.y == c.y
    }
}

pub struct Move {
    pub position: Coordinate,
    pub direction: Direction,
}

#[derive(Debug, Clone)]
struct Entity {
    char: char,
}

#[derive(Debug, Clone)]
pub struct Square {
    char: char,
    passable: bool,
    pushable: bool,
    entity: Option<Entity>,
}

#[derive(PartialEq)]
pub enum SquareType {
    Empty,
    Obstacle,
    Unknown,
}

impl Square {
    pub fn new(t: SquareType) -> Square {
        match t {
            SquareType::Obstacle => Square {
                char: 'X',
                passable: false,
                pushable: true,
                entity: None,
            },
            SquareType::Empty | _ => Square {
                char: '.',
                passable: true,
                pushable: false,
                entity: None,
            },
        }
    }

    fn get_type(&self) -> SquareType {
        match self.char {
            '.' => SquareType::Empty,
            'X' => SquareType::Obstacle,
            _ => SquareType::Unknown,
        }
    }

    fn convert(&mut self, t: SquareType) {
        let square = Square::new(t);
        self.char = square.char;
        self.passable = square.passable;
        self.pushable = square.pushable;
    }

    fn set_entity(&mut self, entity: Entity) {
        self.entity = Some(entity);
    }

    fn remove_entity(&mut self) -> Option<Entity> {
        let entity_copy = self.entity.clone();

        self.entity = None;

        if let Some(entity) = entity_copy {
            Some(entity)
        } else {
            None
        }
    }
}
