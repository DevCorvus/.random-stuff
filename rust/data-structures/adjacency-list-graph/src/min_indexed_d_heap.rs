use std::cmp::{max, min};

pub struct MinIndexedDHeap<T> {
    size: usize,
    degree: usize,
    child: Vec<Option<usize>>,
    parent: Vec<Option<usize>>,
    pm: Vec<Option<usize>>, // Position Map
    im: Vec<Option<usize>>, // Inverse Map
    values: Vec<Option<T>>,
}

impl<T: PartialOrd + Copy> MinIndexedDHeap<T> {
    pub fn new(degree: usize, max_size: usize) -> Self {
        let degree = max(2, degree);
        let capacity = max(degree + 1, max_size);

        let mut child = vec![None; capacity];
        let mut parent = vec![None; capacity];

        for i in 0..capacity {
            if i > 0 {
                parent[i] = Some((i - 1) / degree);
            }
            child[i] = Some(i * degree + 1);
        }

        Self {
            size: 0,
            degree,
            child,
            parent,
            pm: vec![None; capacity],
            im: vec![None; capacity],
            values: vec![None; capacity],
        }
    }

    fn is_empty(&self) -> bool {
        return self.size == 0;
    }

    pub fn contains(&self, ki: usize) -> bool {
        return self.pm[ki].is_some();
    }

    pub fn peek_min_key_index(&self) -> Option<usize> {
        return self.im[0];
    }

    fn poll_min_key_index(&mut self) -> Option<usize> {
        if let Some(min_ki) = self.peek_min_key_index() {
            self.delete(min_ki);
            return Some(min_ki);
        }
        return None;
    }

    fn peek_min_value(&self) -> Option<T> {
        return self.values[self.im[0]?];
    }

    pub fn poll_min_value(&mut self) -> Option<T> {
        if let Some(min_value) = self.peek_min_value() {
            self.delete(self.peek_min_key_index()?);
            return Some(min_value);
        }
        return None;
    }

    pub fn insert(&mut self, ki: usize, value: T) -> bool {
        if self.contains(ki) {
            return false;
        }

        self.pm[ki] = Some(self.size);
        self.im[self.size] = Some(ki);
        self.values[ki] = Some(value);

        self.swim(self.size);
        self.size += 1;

        return true;
    }

    fn get_value_of(&self, ki: usize) -> Option<T> {
        return self.values[ki];
    }

    fn delete(&mut self, ki: usize) -> Option<T> {
        if let Some(i) = self.pm[ki] {
            self.size -= 1;
            self.swap(i, self.size);

            self.sink(i);
            self.swim(i);

            let value = self.values[ki].unwrap();

            self.values[ki] = None;
            self.pm[ki] = None;
            self.im[self.size] = None;

            return Some(value);
        }
        return None;
    }

    fn update(&mut self, ki: usize, value: T) -> Option<T> {
        if let Some(i) = self.pm[ki] {
            let old_value = self.values[ki].unwrap();

            self.values[ki] = Some(value);

            self.sink(i);
            self.swim(i);

            return Some(old_value);
        }
        return None;
    }

    pub fn decrease(&mut self, ki: usize, value: T) {
        if self.contains(ki) && value < self.values[ki].unwrap() {
            self.values[ki] = Some(value);
            self.swim(self.pm[ki].unwrap());
        }
    }

    fn increase(&mut self, ki: usize, value: T) {
        if self.contains(ki) && self.values[ki].unwrap() < value {
            self.values[ki] = Some(value);
            self.sink(self.pm[ki].unwrap());
        }
    }

    fn sink(&mut self, mut i: usize) {
        while let Some(j) = self.min_child(i) {
            self.swap(i, j);
            i = j;
        }
    }

    fn swim(&mut self, mut i: usize) {
        if let Some(j) = self.parent[i] {
            while self.is_less(i, j) {
                self.swap(i, self.parent[i].unwrap());
                i = self.parent[i].unwrap();
            }
        }
    }

    fn min_child(&self, mut i: usize) -> Option<usize> {
        let mut index = None;
        let from = self.child[i].unwrap();
        let to = min(self.size, from + self.degree);

        for j in from..to {
            if self.is_less(j, i) {
                index = Some(i);
                i = j;
            }
        }

        return index;
    }

    fn swap(&mut self, i: usize, j: usize) {
        self.pm[self.im[j].unwrap()] = Some(i);
        self.pm[self.im[i].unwrap()] = Some(j);
        let tmp = self.im[i];
        self.im[i] = self.im[j];
        self.im[j] = tmp;
    }

    fn is_less(&self, i: usize, j: usize) -> bool {
        return self.values[self.im[i].unwrap()].unwrap()
            < self.values[self.im[j].unwrap()].unwrap();
    }
}
