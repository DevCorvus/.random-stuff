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
}

fn main() {
    let mut graph = AdjacencyMatrixGraph::new(4);

    graph.add_undirected_unweighted_edge(0, 1);

    for row in graph.data {
        println!("{:?}", row);
    }
}
