use std::path::Path;

use clap::Parser;
use image::{DynamicImage, GenericImageView, ImageFormat};

use colored::*;

const ASCII_CHARS: [char; 8] = [' ', '.', ',', '-', '~', '+', '=', '@'];
const MAX_INTENSITY: u8 = 255;

fn get_ascii_char(intensity: u8) -> char {
    let mut index = ((intensity as f64 / MAX_INTENSITY as f64) * ASCII_CHARS.len() as f64) as u8;

    if intensity == MAX_INTENSITY {
        index = ASCII_CHARS.len() as u8 - 1
    }

    return ASCII_CHARS[index as usize];
}

fn get_dynamic_step(width: u32, height: u32, max_size: u32) -> u32 {
    let width_scale = width / max_size;
    let height_scale = height / max_size;

    return u32::max(u32::max(width_scale, height_scale), 1);
}

fn generate_ascii(img: DynamicImage, max_size: u32) {
    let (width, height) = img.dimensions();

    let step = get_dynamic_step(width, height, max_size);

    for y in (0..height).step_by((step * 2) as usize) {
        let mut row = String::new();

        for x in (0..width).step_by((step) as usize) {
            let pixel = img.get_pixel(x, y);

            let mut intensity = 0;

            let is_alpha_zero = *(pixel.0.last().unwrap()) == 0;

            if !is_alpha_zero {
                intensity = pixel.0.into_iter().take(3).map(|n| n / 3).sum();
            }

            row.push(get_ascii_char(intensity));
        }

        println!("{}", row);
    }
}

fn generate_colored_ascii(img: DynamicImage, max_size: u32) {
    let (width, height) = img.dimensions();

    let step = get_dynamic_step(width, height, max_size);

    for y in (0..height).step_by((step * 2) as usize) {
        for x in (0..width).step_by((step) as usize) {
            let pixel = img.get_pixel(x, y);

            let mut intensity = 0;

            let is_alpha_zero = *(pixel.0.last().unwrap()) == 0;

            if !is_alpha_zero {
                intensity = pixel.0.into_iter().take(3).map(|n| n / 3).sum();
            }

            print!(
                "{}",
                get_ascii_char(intensity)
                    .to_string()
                    .truecolor(pixel[0], pixel[1], pixel[2])
            );
        }

        println!();
    }
}

/// ASCII Image Generator
#[derive(Parser)]
struct Args {
    /// File path
    path: String,

    /// Max size in characters to keep proportions for width and height
    #[arg(short, long)]
    size: Option<u32>,

    /// Generate with colors (slower)
    #[arg(short, long, action)]
    colored: bool,
}

fn main() {
    let args = Args::parse();

    let image_path = Path::new(&args.path);

    if !image_path.exists() || !image_path.is_file() {
        panic!("File does not exist");
    }

    ImageFormat::from_path(image_path).expect("Unsupported file");

    let img = image::open(image_path).unwrap();

    let max_size = args.size.unwrap_or(200);

    if max_size == 0 {
        panic!("Size 0 is not possible");
    }

    if args.colored {
        generate_colored_ascii(img, max_size);
    } else {
        generate_ascii(img, max_size);
    }
}
