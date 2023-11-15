use std::collections::hash_map::DefaultHasher;
use std::hash::Hasher;

const DEFAULT_SIZE: usize = 100;

struct Node<T> {
    key: String,
    value: T,
    next: Box<Option<Node<T>>>,
}

impl<T> Node<T> {
    fn new(key: &str, value: T) -> Self {
        Self {
            key: key.into(),
            value,
            next: Box::new(None),
        }
    }
}

struct HashTable<T> {
    table: Vec<Option<Node<T>>>,
    size: usize,
    capacity: usize,
}

// TODO: Make it grow and shrink accordingly to avoid hash collisions
impl<T> HashTable<T> {
    fn new() -> Self {
        let mut table: Vec<Option<Node<T>>> = Vec::with_capacity(DEFAULT_SIZE);

        // Ew!
        for _ in 0..DEFAULT_SIZE {
            table.push(None);
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

    fn put(&mut self, key: &str, value: T) {
        let key_hash = self.hash(key);

        let mut curr_node = self.table[key_hash].as_mut();

        if curr_node.is_none() {
            self.table[key_hash] = Some(Node::new(key, value));
            self.size += 1;
            return;
        }

        while let Some(node) = curr_node {
            if node.key == key {
                node.value = value;
                return;
            } else if node.next.is_none() {
                node.next = Box::new(Some(Node::new(key, value)));
                self.size += 1;
                return;
            } else {
                curr_node = (*node.next).as_mut();
            }
        }
    }

    fn get(&self, key: &str) -> Option<&Node<T>> {
        let key_hash = self.hash(key);

        let mut curr_node = self.table[key_hash].as_ref();

        while let Some(node) = curr_node {
            if node.key == key {
                return Some(node);
            }
            curr_node = (*node.next).as_ref();
        }

        return None;
    }

    fn delete(&mut self, key: &str) {
        let key_hash = self.hash(key);

        match self.table[key_hash].as_ref() {
            Some(node) => {
                if node.key == key && node.next.is_none() {
                    self.table[key_hash] = None;
                    self.size -= 1;
                    return;
                }
            }
            None => {
                return;
            }
        }

        let mut curr_node = self.table[key_hash].as_mut();

        while let Some(node) = curr_node {
            if let Some(next) = (*node.next).as_mut() {
                if next.key == key {
                    node.next = Box::new(next.next.take());
                    self.size -= 1;
                    return;
                }
            }
            curr_node = (*node.next).as_mut();
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
