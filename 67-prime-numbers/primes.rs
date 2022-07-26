use std::env;

/// Build and return list of first `n` prime numbers.
fn build_primes(n: u32) -> Vec<u32> {
    const M: usize = 1234567;
    let mut sieve = [false; M];
    let mut primes = Vec::new();
    for k in 2..M {
        if sieve[k] {
            continue;
        }
        primes.push(k as u32);
        if primes.len() == n as usize {
            break;
        }
        for l in (k..M).step_by(k) {
            sieve[l] = true;
        }
    }
    primes
}

fn main() {
    // Print first `n` prime numbers (default: 10)
    let arg = env::args().nth(1);
    let n = match arg {
        Some(s) => s.parse::<u32>().unwrap_or(10),
        None => 10,
    };
    let primes = build_primes(n);
    println!("{:?}", primes);
}
