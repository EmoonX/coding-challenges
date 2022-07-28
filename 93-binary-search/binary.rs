use rand::{thread_rng, Rng};
use std::collections::BTreeSet;

fn main() {
    const M: i32 = 64;
    let n = 16;
    let mut set = BTreeSet::new();
    let mut rng = thread_rng();
    while set.len() < n {
        let k = rng.gen_range(0..M);
        set.insert(k);
    }
    let vec = Vec::from_iter(set);
    println!("{:?}", vec);
}
