use std::collections::VecDeque;

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

    fn breadth_first_search(&self, start: usize) {
        let mut visited = vec![false; self.size];
        let mut queue = VecDeque::new();

        visited[start] = true;
        queue.push_back(start);

        while let Some(i) = queue.pop_front() {
            println!("{}", i);
            for (next, weight) in self.data[i].iter().enumerate() {
                if *weight != 0 && !visited[next] {
                    visited[next] = true;
                    queue.push_back(next);
                }
            }
        }
    }
}

fn main() {
    let mut graph = AdjacencyMatrixGraph::new(4);

    graph.add_undirected_unweighted_edge(0, 1);
    graph.add_undirected_unweighted_edge(0, 2);
    graph.add_undirected_unweighted_edge(1, 3);

    for row in &graph.data {
        println!("{:?}", row);
    }

    println!("DFS");
    graph.depth_first_search(0);

    println!("BFS");
    graph.breadth_first_search(0);
}
