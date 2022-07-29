use std::cmp::{max, min};
use std::env::args;

/// Build a Vec of all possible solutions for the `n`-queens problem.
fn find_solutions(n: usize, queens: &mut Vec<usize>) -> Vec<Vec<usize>> {
    let mut solutions = Vec::new();
    if queens.len() == n {
        let mut vec = vec![0; n];
        for (i, j) in queens.iter().enumerate() {
            vec[i] = *j;
        }
        solutions.push(vec);
        return solutions;
    }
    for j in 1..=n {
        if (! queens.contains(&j)) && is_valid_diagonal(queens, j) {
            queens.push(j);
            let mut vec = find_solutions(n, queens);
            solutions.append(&mut vec);
            queens.pop();
        }
    }
    solutions
}

/// Check if no queen diagonally attacks current row in `j`th column.
fn is_valid_diagonal(queens: &Vec<usize>, j: usize) -> bool {
    for k in 1..=queens.len() {
        let i = queens[queens.len() - k];
        if max(i, j) - min(i, j) == k {
            return false;
        }
    }
    return true;
}

fn main() {
    let arg = args().nth(1);
    let n = match arg {
        Some(s) => s.parse().unwrap_or(8),
        None => 8,
    };
    let mut queens = Vec::new();
    let solutions = find_solutions(n, &mut queens);
    let total = solutions.len();
    for sol in solutions {
        println!("{:?}", sol);
    }
    println!("{}", total);
}
