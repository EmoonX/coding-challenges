
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
    let primes = build_primes(1000);
    println!("{:?}", primes);
}
