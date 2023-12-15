use std::collections::HashMap;

struct Edge {
    #[allow(unused)]
    from: usize,
    to: usize,
    #[allow(unused)]
    cost: isize,
}

pub struct AdjacencyListGraph {
    data: HashMap<usize, Vec<Edge>>,
    size: usize,
}

impl AdjacencyListGraph {
    pub fn new() -> Self {
        Self {
            data: HashMap::new(),
            size: 0,
        }
    }

    pub fn add(&mut self, from: usize, to: usize, cost: isize) {
        let edge = Edge { from, to, cost };

        match self.data.get_mut(&from) {
            Some(v) => {
                v.push(edge);
            }
            None => {
                let mut v = Vec::new();
                v.push(edge);

                self.data.insert(from, v);
            }
        };

        // To improve
        if from != to {
            self.size += 1;
        }
    }

    pub fn depth_first_search(&self, start: usize) -> usize {
        let mut count: usize = 0;
        let mut visited = vec![false; self.size];

        let mut stack = Vec::new();

        stack.push(start);
        visited[start] = true;

        while let Some(i) = stack.pop() {
            count += 1;

            if let Some(edges) = self.data.get(&i) {
                for edge in edges {
                    if !visited[edge.to] {
                        stack.push(edge.to);
                        visited[edge.to] = true;
                    }
                }
            }
        }

        return count;
    }
}
