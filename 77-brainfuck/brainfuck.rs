mod util;

use std::io::{BufRead, stdin, stdout, Write};

use util::colorize;

/// Size of cell array.
const N: usize = 30_000;

/// The Brainfuck machine.
struct Machine {
    /// Data cells as array of bytes.
    cells: [u8; N],
    /// Current data pointer position.
    pos: usize,
    /// Program defined as a sequence of single characters (`><+-.,[]`).
    program: String,
}

impl Machine {
    /// Creates a new `Machine` with given input program.
    fn new(program: String) -> Self {
        let mut cells = [0; N];
        Self {
            cells: cells,
            pos: 0,
            program: program,
        }
    }

    /// Runs machine, iterating through commands.
    fn run(&self) {
        for c in self.program.chars() {
            self.parse(c);
        }
    }

    /// Parses single command.
    fn parse(&self, command: char) {
        match command {
            '>' => self.increment_pointer(),
            '<' => self.decrement_pointer(),
            '+' => self.increment_byte(),
            '-' => self.decrement_byte(),
            '.' => self.output(),
            ',' => self.input(),
            '[' => self.open_loop(),
            ']' => self.close_loop(),
            _ => (),
        }
    }
    
    // (The following method descriptions were acquired from Wikipedia)

    /// Increments the data pointer (to point to the next cell to the right).
    fn increment_pointer(&self) {
        println!(
            "{} Moving pointer to the right [{}]",
            colorize('>', "blue"), self.pos
        );
    }

    /// Decrements the data pointer (to point to the next cell to the left).
    fn decrement_pointer(&self) {
        println!(
            "{} Moving pointer to the left [{}]",
            colorize('<', "blue"), self.pos
        );
    }

    /// Increments (increases by one) the byte at the data pointer.
    fn increment_byte(&self) {
        println!(
            "{} Incrementing byte in [{}] to {}",
            colorize('+', "green"), self.pos, self.cells[self.pos]
        );
    }

    /// Decrements (decreases by one) the byte at the data pointer.
    fn decrement_byte(&self) {
        println!(
            "{} Decrementing byte in [{}] to {}",
            colorize('-', "red"), self.pos, self.cells[self.pos]
        );
    }

    /// Outputs the byte at the data pointer. 
    fn output(&self) {
        println!("{} Outputting... ", colorize('.', "yellow"));
    }

    /// Accepts one byte of input,
    /// storing its value in the byte at the data pointer.
    fn input(&self) {
        println!("{} Waiting for input...", colorize(',', "cyan"));
    }

    /// If the byte at the data pointer is zero, then
    /// instead of moving the instruction pointer forward to the next command,
    /// jumps it forward to the command after the matching `]` command. 
    fn open_loop(&self) {
        println!("{} Opening loop", colorize('[', "purple"))
    }

    /// If the byte at the data pointer is nonzero, then
    /// instead of moving the instruction pointer forward to the next command,
    /// jumps it back to the command after the matching `[` command.
    fn close_loop(&self) {
        println!("{} Closing loop", colorize(']', "purple"))
    }
}

fn main() {
    while true {
        print!(" ");
        stdout().flush().unwrap();
        let mut input = String::new();
        stdin().lock().read_line(&mut input).unwrap();
        let mut machine = Machine::new(input);
        machine.run();
    }
}
