pub struct UnionFind {
    parents: Vec<usize>,
    sizes: Vec<usize>,
    size: usize,
    num_sets: usize,
}

impl UnionFind {
    pub fn new(n: usize) -> Self {
        Self {
            parents: Vec::from_iter(0..n),
            sizes: vec![1; n],
            size: n,
            num_sets: n,
        }
    }

    pub fn find(&mut self, i: usize) -> usize {
        if self.parents[i] == i {
            return i;
        } else {
            let next_parent = self.find(self.parents[i]);
            self.parents[i] = next_parent;
            return next_parent;
        }
    }

    pub fn union(&mut self, i: usize, j: usize) {
        let i_root = self.find(i);
        let j_root = self.find(j);

        if i_root == j_root {
            return;
        }

        if self.sizes[i_root] < self.sizes[j_root] {
            self.sizes[j_root] += self.sizes[i_root];
            self.sizes[i_root] = 0;
            self.parents[i_root] = j_root;
        } else {
            self.sizes[i_root] += self.sizes[j_root];
            self.sizes[j_root] = 0;
            self.parents[j_root] = i_root;
        }

        self.num_sets -= 1;
    }
}
