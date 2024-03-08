use colored::{ColoredString, Colorize};

/// Stylizes string with given terminal background color.
pub fn colorize(string: String, bg_color: &str) -> ColoredString {
    string.bright_white().on_color(bg_color).bold()
}
