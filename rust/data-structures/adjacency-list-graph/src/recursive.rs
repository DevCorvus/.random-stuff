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

    pub fn depth_first_search(&self, at: usize) -> usize {
        let mut visited = vec![false; self.size];
        return self._depth_first_search(at, &mut visited);
    }

    fn _depth_first_search(&self, at: usize, visited: &mut Vec<bool>) -> usize {
        if visited[at] {
            return 0;
        }

        visited[at] = true;
        let mut count: usize = 1;

        if let Some(edges) = self.data.get(&at) {
            for edge in edges {
                count += self._depth_first_search(edge.to, visited);
            }
        }

        return count;
    }
}
