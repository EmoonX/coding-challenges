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
}

impl Machine {
    /// Creates a new `Machine` with given input program.
    fn new() -> Self {
        Self {
            cells: [0; N],
            pos: 0,
        }
    }

    /// Runs given program on machine, one command by one.
    fn run(&mut self, program: &str) {
        let chars = program.chars();
        for (_i, command) in chars.enumerate() {
            self.parse(command);
        }
    }

    /// Parses single command.
    fn parse(&mut self, command: char) {
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
    fn increment_pointer(&mut self) {
        self.pos += 1;
        println!(
            "{} Moving pointer to the right: [{}]",
            colorize('>', "blue"), self.pos
        );
    }

    /// Decrements the data pointer (to point to the next cell to the left).
    fn decrement_pointer(&mut self) {
        self.pos -= 1;
        println!(
            "{} Moving pointer to the left:  [{}]",
            colorize('<', "blue"), self.pos
        );
    }

    /// Increments (increases by one) the byte at the data pointer.
    fn increment_byte(&mut self) {
        self.cells[self.pos] += 1;
        println!(
            "{} Incrementing byte in [{}] to {}",
            colorize('+', "green"), self.pos, self.cells[self.pos]
        );
    }

    /// Decrements (decreases by one) the byte at the data pointer.
    fn decrement_byte(&mut self) {
        self.cells[self.pos] -= 1;
        println!(
            "{} Decrementing byte in [{}] to {}",
            colorize('-', "red"), self.pos, self.cells[self.pos]
        );
    }

    /// Outputs the byte at the data pointer. 
    fn output(&self) {
        let character = self.cells[self.pos] as char;
        println!(
            "{} Outputting... {}",
            colorize('.', "yellow"), character
        );
    }

    /// Accepts one byte of input,
    /// storing its value in the byte at the data pointer.
    fn input(&mut self) {
        print!(
            "{} Waiting for input... ",
            colorize(',', "cyan")
        );
        stdout().flush().unwrap();
        let mut input = String::new();
        stdin().lock().read_line(&mut input).unwrap();
        let character = input.bytes().nth(0).unwrap();
        self.cells[self.pos] = character;
    }

    /// If the byte at the data pointer is zero, then
    /// instead of moving the instruction pointer forward to the next command,
    /// jumps it forward to the command after the matching `]` command. 
    fn open_loop(&self) {
        println!(
            "{} Opening loop",
            colorize('[', "purple")
        );
    }

    /// If the byte at the data pointer is nonzero, then
    /// instead of moving the instruction pointer forward to the next command,
    /// jumps it back to the command after the matching `[` command.
    fn close_loop(&self) {
        println!(
            "{} Closing loop",
            colorize(']', "purple")
        )
    }
}

fn main() {
    loop {
        print!(" ");
        stdout().flush().unwrap();
        let mut input = String::new();
        stdin().lock().read_line(&mut input).unwrap();
        let mut machine = Machine::new();
        machine.run(&input);
    }
}
