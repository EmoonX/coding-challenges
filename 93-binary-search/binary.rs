use colored::Colorize;
use rand::{thread_rng, Rng};
use regex::Regex;
use std::collections::BTreeSet;

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

/// Pretty-prints a string representing a Vec,
/// highlighting the value of `k` in it with terminal magic.
fn pretty_print(vec_str: &String, k: i32) {
    let re_str = format!(r"{}([,\]])", k);
    let re = Regex::new(re_str.as_str()).unwrap();
    let str_fmt = format!(">>> {} <<<", k);
    let str_style = str_fmt.green().bold();
    let rep = format!(r"{}$1", str_style);
    let result = re.replace(&vec_str, &rep);
    println!("{}", result);
}

fn main() {
    // Generate ordered set of N distinct random numbers in range 0..M
    const M: i32 = 64;
    const N: usize = 16;
    let mut set = BTreeSet::new();
    let mut rng = thread_rng();
    while set.len() < N {
        let k = rng.gen_range(0..M);
        set.insert(k);
    }
    // Create correspondent Vec from set iterator
    let vec = Vec::from_iter(set);
    let vec_str = format!("{:?}", vec);
    println!("{}", vec_str);

    for _ in 0..N {
        // Search for random value in Vec
        let k = rng.gen_range(0..M);
        print!(
            "\nSearching for value {}... ",
            k.to_string().yellow().bold()
        );
        let i = find(&vec, k);
        if i < N && vec[i] == k {
            println!("found!");
            pretty_print(&vec_str, k);
        }
    }
    println!();
}
