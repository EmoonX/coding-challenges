use colored::{ColoredString, Colorize};

/// Stylizes character with given terminal background color.
pub fn colorize(character: char, bg_color: &str) -> ColoredString {
    let s = format!(" {} ", character);
    s.bright_white().on_color(bg_color).bold()
}
