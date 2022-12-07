use std::io::{BufRead, stdin, stdout, Write};

const N: usize = 30_000;

struct Machine {
    cells: [u8; N],
    ptr: *mut u8, 
    program: String,
}

impl Machine {

    fn new(input: String) -> Self {
        let mut cells = [0; N];
        Self {
            cells: cells,
            ptr: cells.as_mut_ptr(),
            program: input,
        }
    }

    fn run(&self) {
        for c in self.program.chars() {
            self.parse(c);
        }
    }

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

    fn increment_pointer(&self) {
        println!(">: Incrementing pointer");
    }

    fn decrement_pointer(&self) {
        println!("<: Decrementing pointer");
    }

    fn increment_byte(&self) {
        println!("+: Incrementing byte");
    }

    fn decrement_byte(&self) {
        println!("-: Decrementing byte");
    }

    fn output(&self) {
        println!(".: Outputting");
    }

    fn input(&self) {
        println!(",: Waiting for input...");
    }

    fn open_loop(&self) {
        println!("[: Opening loop")
    }

    fn close_loop(&self) {
        println!("]: Closing loop")
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
