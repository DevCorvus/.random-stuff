use std::collections::hash_map::DefaultHasher;
use std::hash::Hasher;

// There are at least three types of probing for Open Addressing techniques
// 1. Linear probing
// 2. Quadratic probing (Current)
// 3. Double hashing

const DEFAULT_SIZE: usize = 10;

struct Node<T> {
    key: String,
    value: T,
}

enum HashNode<T> {
    Pair(Option<Node<T>>),
    Tombstone,
}

impl<T> Node<T> {
    fn new(key: &str, value: T) -> Self {
        Self {
            key: key.into(),
            value,
        }
    }
}

struct HashTable<T> {
    table: Vec<HashNode<T>>,
    size: usize,
    capacity: usize,
}

// TODO: Make it grow and shrink accordingly to avoid hash collisions
impl<T> HashTable<T> {
    fn new() -> Self {
        let mut table: Vec<HashNode<T>> = Vec::with_capacity(DEFAULT_SIZE);

        // Ew!
        for _ in 0..DEFAULT_SIZE {
            table.push(HashNode::Pair(None));
        }

        Self {
            table,
            size: 0,
            capacity: DEFAULT_SIZE,
        }
    }

    fn hash(&self, key: &str) -> usize {
        let mut hasher = DefaultHasher::new();
        hasher.write(key.as_bytes());

        let result = hasher.finish();
        return (result as usize) % self.capacity;
    }

    fn probe(&self, offset: usize, x: usize) -> usize {
        // One of many possible Quadratic probing functions
        // Does this one avoid cycles? I have no idea
        return (offset + (x * x)) % self.capacity;
    }

    fn put(&mut self, key: &str, value: T) {
        let mut index = self.hash(key);
        let mut x: usize = 1;

        while let HashNode::Pair(Some(node)) = &mut self.table[index] {
            if node.key == key {
                node.value = value;
                return;
            }
            index = self.probe(index, x);
            x += 1;
        }

        self.table[index] = HashNode::Pair(Some(Node::new(key, value)));
        self.size += 1;
    }

    fn get_index(&mut self, key: &str) -> Option<usize> {
        let mut index = self.hash(key);
        let mut x: usize = 1;

        let mut first_tombstone_index: Option<usize> = None;
        let mut visited_indexes: Vec<usize> = Vec::with_capacity(self.capacity);

        loop {
            if visited_indexes.contains(&index) {
                return None;
            }

            match &mut self.table[index] {
                HashNode::Pair(None) => {
                    return None;
                }
                HashNode::Pair(Some(node)) => {
                    if node.key == key {
                        if let Some(tombstone_index) = first_tombstone_index {
                            let current_node = match &mut self.table[index] {
                                HashNode::Pair(pair) => pair.take(),
                                _ => panic!("Could not move current node"),
                            };
                            self.table[tombstone_index] = HashNode::Pair(current_node);
                            return Some(tombstone_index);
                        }
                        return Some(index);
                    }
                }
                HashNode::Tombstone => {
                    if first_tombstone_index.is_none() {
                        first_tombstone_index = Some(index);
                    }
                }
            }
            visited_indexes.push(index);
            index = self.probe(index, x);
            x += 1;
        }
    }

    fn get(&mut self, key: &str) -> Option<&Node<T>> {
        match self.get_index(key) {
            Some(index) => {
                if let HashNode::Pair(Some(node)) = &self.table[index] {
                    return Some(node);
                }
                unreachable!();
            }
            None => None,
        }
    }

    fn delete(&mut self, key: &str) {
        let mut index = self.hash(key);
        let mut x: usize = 1;

        while let HashNode::Pair(Some(node)) = &self.table[index] {
            if node.key == key {
                self.table[index] = HashNode::Tombstone;
                self.size -= 1;
                return;
            }
            index = self.probe(index, x);
            x += 1;
        }
    }
}

fn main() {
    let mut ht: HashTable<i32> = HashTable::new();
    println!("Capacity: {}", ht.capacity);
    println!("Size: {}", ht.size);

    ht.put("uwu", 69);
    ht.put("sublime", 4);
    ht.put("cheno", 13);
    ht.put("rajoy", 36);

    println!("Size: {}", ht.size);

    ht.delete("rajoy");

    println!("Size: {}", ht.size);

    if let Some(node) = ht.get("uwu") {
        println!("{}: {}", node.key, node.value);
    }

    if let Some(node) = ht.get("sublime") {
        println!("{}: {}", node.key, node.value);
    }

    if let Some(node) = ht.get("cheno") {
        println!("{}: {}", node.key, node.value);
    }

    if let Some(node) = ht.get("rajoy") {
        println!("{}: {}", node.key, node.value);
    }
}
