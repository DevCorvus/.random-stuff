fn lsb(n: usize) -> usize {
    return n & n.wrapping_neg(); // Lowest one bit
}

// Also called Binary Indexed Tree
struct FenwickTree {
    tree: Vec<i32>,
}

impl FenwickTree {
    fn new(mut values: Vec<i32>) -> Self {
        // Tree is a vec with 1-based indexing
        let mut tree = vec![0];

        tree.append(&mut values);
        let tree_len = tree.len();

        for i in 1..tree_len {
            let parent = i + lsb(i);
            if parent < tree_len {
                tree[parent] += tree[i];
            }
        }

        Self { tree }
    }

    fn prefix_sum(&self, mut i: usize) -> i32 {
        let mut sum = 0;

        while i != 0 {
            sum += self.tree[i];
            i &= !lsb(i); // Equivalent to: i -= lsb(i as i32);
        }

        return sum;
    }

    fn sum(&self, left: usize, right: usize) -> i32 {
        assert!(right >= left);
        return self.prefix_sum(right) - self.prefix_sum(left - 1);
    }

    fn get(&self, i: usize) -> i32 {
        return self.sum(i, i);
    }

    fn add(&mut self, mut i: usize, v: i32) {
        let tree_len = self.tree.len();

        while i < tree_len {
            self.tree[i] += v;
            i += lsb(i);
        }
    }

    fn set(&mut self, i: usize, v: i32) {
        self.add(i, v - self.get(i));
    }
}

fn main() {
    let values = vec![3, 4, -2, 7, 3, 11, 5, -8, -9, 2, 4, -8];

    let mut ft = FenwickTree::new(values);

    for (i, n) in ft.tree.clone().into_iter().enumerate() {
        println!("{}: {}", i, n);
    }

    // All the following operations over indexes are 1-based
    println!("Index 1: {}", ft.get(1));
    ft.set(1, 2);
    println!("Index 1 after set 2: {}", ft.get(1));
    ft.add(1, 2);
    println!("Index 1 after add 2: {}", ft.get(1));

    println!("Sum between index 5 and 8: {}", ft.sum(5, 8));
}
