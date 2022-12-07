use std::io::{BufRead, stdin, stdout, Write};

/// Size of cell array.
const N: usize = 30_000;

/// The Brainfuck machine.
struct Machine {
    /// Data cells as array of bytes.
    cells: [u8; N],
    /// Movable data pointer.
    ptr: *mut u8,
    /// Program defined as a sequence of single characters (`><+-.,[]`).
    program: String,
}

impl Machine {
    /// Creates a new `Machine` with given input program.
    fn new(program: String) -> Self {
        let mut cells = [0; N];
        Self {
            cells: cells,
            ptr: cells.as_mut_ptr(),
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
        println!("(>) Moving pointer to ");
    }

    /// Decrements the data pointer (to point to the next cell to the left).
    fn decrement_pointer(&self) {
        println!("(<) Decrementing pointer");
    }

    /// Increments (increases by one) the byte at the data pointer.
    fn increment_byte(&self) {
        println!("(+) Incrementing byte");
    }

    /// Decrements (decreases by one) the byte at the data pointer.
    fn decrement_byte(&self) {
        println!("(-) Decrementing byte");
    }

    /// Outputs the byte at the data pointer. 
    fn output(&self) {
        println!("(.) Outputting");
    }

    /// Accepts one byte of input,
    /// storing its value in the byte at the data pointer.
    fn input(&self) {
        println!("(,) Waiting for input...");
    }

    /// If the byte at the data pointer is zero, then
    /// instead of moving the instruction pointer forward to the next command,
    /// jumps it forward to the command after the matching `]` command. 
    fn open_loop(&self) {
        println!("([) Opening loop")
    }

    /// If the byte at the data pointer is nonzero, then
    /// instead of moving the instruction pointer forward to the next command,
    /// jumps it back to the command after the matching `[` command.
    fn close_loop(&self) {
        println!("(]) Closing loop")
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
