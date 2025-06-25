use std::collections::{BinaryHeap, HashSet};
use std::hash::Hash;

pub struct UniqueBinaryHeap<T>
where
    T: Ord + Eq + Hash + Clone,
{
    heap: BinaryHeap<T>,
    seen: HashSet<T>,
}

impl<T> UniqueBinaryHeap<T>
where
    T: Ord + Eq + Hash + Clone,
{
    pub fn new() -> Self {
        UniqueBinaryHeap {
            heap: BinaryHeap::new(),
            seen: HashSet::new(),
        }
    }

    pub fn push(&mut self, item: T) {
        if self.seen.insert(item.clone()) {
            // insert returns true if the element was not present
            self.heap.push(item);
        }
    }

    pub fn pop(&mut self) -> Option<T> {
        let popped_item = self.heap.pop();
        if let Some(item) = &popped_item {
            self.seen.remove(item);
        }
        popped_item
    }

    pub fn peek(&self) -> Option<&T> {
        self.heap.peek()
    }

    pub fn is_empty(&self) -> bool {
        self.heap.is_empty()
    }

    pub fn len(&self) -> usize {
        self.heap.len()
    }
}
