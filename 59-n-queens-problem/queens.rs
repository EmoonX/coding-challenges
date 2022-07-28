use std::cmp::{max, min};

const N: usize = 8;

/// Build a Vec of all possible solutions for the N-queens problem.
fn find_solutions(queens: &mut Vec<usize>) -> Vec<[usize; 8]> {
    let mut solutions = Vec::new();
    if queens.len() == N {
        let mut arr = [0; N];
        for (i, j) in queens.iter().enumerate() {
            arr[i] = *j;
        }
        solutions.push(arr);
        return solutions;
    }
    for j in 1..=N {
        if (! queens.contains(&j)) && is_valid_diagonal(queens, j) {
            queens.push(j);
            let mut vec = find_solutions(queens);
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
    let mut queens = Vec::new();
    let solutions = find_solutions(&mut queens);
    let total = solutions.len();
    for sol in solutions {
        println!("{:?}", sol);
    }
    println!("{}", total);
}
