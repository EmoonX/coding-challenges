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

    fn parse(command: char) {
        match command {
            '>' => println!("Hello, world!"),
            _ => todo!(),
        }
    }
}

fn main() {
    while true {
        print!(" ");
        stdout().flush().unwrap();
        let mut input = String::new();
        stdin().lock().read_line(&mut input).unwrap();
        let mut machine = Machine::new(input);
    }
}
