struct AdjacencyMatrixGraph {
    data: Vec<Vec<usize>>,
    size: usize,
}

impl AdjacencyMatrixGraph {
    fn new(size: usize) -> Self {
        Self {
            data: vec![vec![0; size]; size],
            size,
        }
    }

    fn add_directed_edge(&mut self, from: usize, to: usize, weight: usize) {
        if from < self.size && to < self.size {
            self.data[from][to] = weight;
        }
    }

    fn add_undirected_edge(&mut self, from: usize, to: usize, weight: usize) {
        self.add_directed_edge(from, to, weight);
        self.add_directed_edge(to, from, weight);
    }

    fn add_undirected_unweighted_edge(&mut self, from: usize, to: usize) {
        self.add_undirected_edge(from, to, 1);
    }

    fn depth_first_search(&self, start: usize) {
        let mut visited = vec![false; self.size];
        self._depth_first_search(start, &mut visited);
    }

    fn _depth_first_search(&self, at: usize, visited: &mut Vec<bool>) {
        if visited[at] {
            return;
        }

        visited[at] = true;
        println!("{}", at);

        for (i, weight) in self.data[at].iter().enumerate() {
            if *weight != 0 {
                self._depth_first_search(i, visited);
            }
        }
    }
}

fn main() {
    let mut graph = AdjacencyMatrixGraph::new(4);

    graph.add_directed_edge(0, 1, 1);
    graph.add_directed_edge(1, 3, 1);
    graph.add_directed_edge(3, 2, 1);
    graph.add_directed_edge(2, 1, 1);
    graph.add_directed_edge(2, 3, 1);

    for row in &graph.data {
        println!("{:?}", row);
    }

    graph.depth_first_search(3);
}
