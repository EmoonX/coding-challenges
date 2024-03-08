mod util;

use std::{
    io::{BufRead, stdin, stdout, Write},
    thread::sleep,
    time::Duration,
};
use util::colorize;

/// Size of cell array.
const N: usize = 30_000;

/// The Brainfuck machine.
struct Machine<'a> {
    /// Data cells as array of bytes.
    cells: [i8; N],
    /// Current data pointer position.
    pos: usize,
    /// Program commands as slice of bytes.
    program: &'a[u8],
    /// Index of current command.
    command_idx: usize,
    /// Current loop depth, starting at zero.
    loop_depth: usize,
    /// Buffer for characters outputted by `.` command.
    output_buffer: String
}

impl<'a> Machine<'a> {
    /// Creates a new `Machine` with given input program.
    pub fn new(input: &'a str) -> Self {
        Self {
            cells: [0; N],
            pos: 0,
            program: input.trim().as_bytes(),
            command_idx: 0,
            loop_depth: 0,
            output_buffer: String::new(),
        }
    }

    /// Runs given program on machine, one command by one.
    pub fn run(&mut self) {
        while self.command_idx < self.program.len() {
            print!(" ({:3}) ", self.command_idx);
            let command = self.program[self.command_idx] as char;
            self.parse(command);
            self.command_idx += 1;
            sleep(Duration::from_millis(2));
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
            '[' => self.loop_start(),
            ']' => self.loop_end(),
            _ => (),
        }
    }
    
    // --- (the following method descriptions were acquired from Wikipedia)

    /// Increments the data pointer (to point to the next cell to the right).
    fn increment_pointer(&mut self) {
        self.print_command(
            '>', "blue",
            format!("Moving pointer to the right: [{}]\n", self.pos)
        );
        self.pos += 1;
    }

    /// Decrements the data pointer (to point to the next cell to the left).
    fn decrement_pointer(&mut self) {
        self.print_command(
            '<', "blue",
            format!("Moving pointer to the left: [{}]\n", self.pos)
        );
        self.pos -= 1;
    }

    /// Increments (increases by one) the byte at the data pointer.
    fn increment_byte(&mut self) {
        self.print_command(
            '+', "green",
            format!(
                "Incrementing byte in [{}] to {}\n",
                self.pos, self.cells[self.pos]
            )
        );
        self.cells[self.pos] += 1;
    }

    /// Decrements (decreases by one) the byte at the data pointer.
    fn decrement_byte(&mut self) {
        self.print_command(
            '-', "red",
            format!(
                "Decrementing byte in [{}] to {}\n",
                self.pos, self.cells[self.pos]
            )
        );
        self.cells[self.pos] -= 1;
    }

    /// Outputs the byte at the data pointer as an character,
    /// and adds it to the output buffer.
    fn output(&mut self) {
        self.print_command(
            '.', "yellow",
            "Outputting... ".to_string()
        );        
        let value = self.cells[self.pos];
        let character = value as u8 as char;
        if character.is_alphanumeric() {
            print!("{}", colorize(character.to_string(), "white"));
        }
        self.output_buffer.push(character);
        println!();
    }

    /// Accepts one byte of input,
    /// storing its value in the byte at the data pointer.
    fn input(&mut self) {
        self.print_command(
            ',', "cyan",
            "Waiting for input... ".to_string()
        );
        stdout().flush().unwrap();
        let mut input = String::new();
        stdin().lock().read_line(&mut input).unwrap();
        let character = input.bytes().nth(0).unwrap();
        self.cells[self.pos] = character as i8;
    }

    /// If the byte at the data pointer is zero, then
    /// instead of moving the instruction pointer forward to the next command,
    /// jumps it forward to the command after the matching `]` command. 
    fn loop_start(&mut self) {
        if self.cells[self.pos] != 0 {
            self.print_command(
                '[', "purple",
                "Loop start\n".to_string()
            );
            self.loop_depth += 1;
        } else {
            self.print_command(
                '[', "gray",
                "Loop start... not\n".to_string()
            );
            self.jump_to_matching_bracket(1);
        }
    }

    /// If the byte at the data pointer is nonzero, then
    /// instead of moving the instruction pointer forward to the next command,
    /// jumps it back to the command after the matching `[` command.
    fn loop_end(&mut self) {
        if self.cells[self.pos] == 0 {
            self.loop_depth -= 1;
            self.print_command(
                ']', "purple",
                "Loop end\n".to_string()
            );
        } else {
            self.print_command(
                ']', "gray",
                "Loop end... not\n".to_string()
            );
            self.jump_to_matching_bracket(-1);
        }
    }

    // --- (descriptions end)

    /// Moves command index to matching bracket's cell in the direction
    /// of `offset`, ignoring intermediate brackets.
    fn jump_to_matching_bracket(&mut self, offset: isize) {
        let mut count = offset;
        while count != 0 {
            let idx = (self.command_idx as isize + offset) as usize;
            self.command_idx = idx;
            match self.program[self.command_idx] as char {
                '[' => count += 1,
                ']' => count -= 1,
                _ => ()
            };
        }
    }

    /// Prints command's symbol and message.
    fn print_command(&mut self, symbol: char, color: &str, message: String) {
        let label = colorize(format!(" {} ", symbol), color);
        print!("{}", " ".repeat(4 * self.loop_depth));
        print!("{} {}", label, message);
    }

    /// Prints machine's output buffer content, if any.
    pub fn show_output(&self) {
        println!();
        if ! self.output_buffer.is_empty() {
            println!("{}", self.output_buffer);
        }
    }
}

fn main() {
    loop {
        print!(" ");
        stdout().flush().unwrap();
        let mut input = String::new();
        stdin().lock().read_line(&mut input).unwrap();
        let mut machine = Machine::new(&input);
        machine.run();
        machine.show_output();
    }
}
