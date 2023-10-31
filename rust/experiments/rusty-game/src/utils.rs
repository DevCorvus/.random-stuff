use super::core::GridBoundaries;
use console::Term;
use std::{error::Error, num::ParseFloatError};

pub fn get_boundaries(stdout: &Term) -> Result<GridBoundaries, Box<dyn Error>> {
    println!("Y: ");
    let y = stdout.read_line()?.parse::<usize>()?;
    println!("X: ");
    let x = stdout.read_line()?.parse::<usize>()?;

    Ok(GridBoundaries { x, y })
}

pub fn to_fixed(num: f64, digits: usize) -> Result<f64, ParseFloatError> {
    format!("{:.1$}", num, digits).parse::<f64>()
}
