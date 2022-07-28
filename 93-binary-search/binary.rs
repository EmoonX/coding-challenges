use rand::{thread_rng, Rng};
use std::collections::BTreeSet;
use std::io::{self, Write};

/// Search (by binary seach) for the value `k` in `vec`, returning
/// the first index `i` where `vec[i] >= k` (or `vec.len()` if none).
fn find(vec: &Vec<i32>, k: i32) -> usize {
    binary_search(vec, 0, vec.len() - 1, k)
}

/// Applies binary search on the interval `[l, r]` of `vec`.
fn binary_search(vec: &Vec<i32>, l: usize, r: usize, k: i32) -> usize {
    let m = (l + r) / 2;
    if vec[m] > k {
        if m == l {
            l
        } else {
            binary_search(vec, l, m-1, k)
        }
    } else if vec[m] < k {
        if m == r {
            r+1
        } else {
            binary_search(vec, m+1, r, k)
        }
    } else { m }
}

fn main() {
    const M: i32 = 64;
    const N: usize = 16;
    let mut set = BTreeSet::new();
    let mut rng = thread_rng();
    while set.len() < N {
        let k = rng.gen_range(0..M);
        set.insert(k);
    }
    let vec = Vec::from_iter(set);
    println!("{:?}", vec);

    for _ in 0..N {
        let k = rng.gen_range(0..M);
        print!("Searching for value {}... ", k);
        io::stdout().flush().unwrap();
        let i = find(&vec, k);
        if i < N && vec[i] == k {
            println!("found! (index {})", i);
        } else {
            print!("not found. ");
            if (1..=N-1).contains(&i) {
                println!(
                    "(between values {} (index {}) and {} (index {}))",
                    vec[i-1], i-1, vec[i], i
                );
            } else {
                println!();
            }
        }
    }
}
