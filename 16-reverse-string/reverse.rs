use std::io::stdin;

fn main() {
    let mut s = String::new();
    stdin().read_line(&mut s).unwrap();
    let rev = s.chars().rev();
    for c in rev {
        if c != '\n' {
            print!("{}", c);
        }
    }
    println!();
}
