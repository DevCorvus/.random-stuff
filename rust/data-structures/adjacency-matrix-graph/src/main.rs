use std::collections::VecDeque;

struct AdjacencyMatrixGraph {
    data: Vec<Vec<Option<isize>>>,
    size: usize,
    edges: usize,
}

impl AdjacencyMatrixGraph {
    fn new(size: usize) -> Self {
        let mut data = vec![vec![None; size]; size];

        for i in 0..size {
            data[i][i] = Some(0);
        }

        Self {
            data,
            size,
            edges: 0,
        }
    }

    fn add_directed_edge(&mut self, from: usize, to: usize, weight: isize) {
        if from < self.size && to < self.size {
            self.data[from][to] = Some(weight);
            self.edges += 1;
        }
    }

    fn add_undirected_edge(&mut self, from: usize, to: usize, weight: isize) {
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
            if weight.is_some() {
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
                if weight.is_some() && !visited[next] {
                    visited[next] = true;
                    queue.push_back(next);
                }
            }
        }
    }

    fn bellman_ford(&self, start: usize) -> Vec<isize> {
        let mut distances = vec![isize::MAX; self.size];
        distances[start] = 0;

        for _ in 0..self.size - 1 {
            for i in 0..self.size {
                for j in 0..self.size {
                    if let Some(distance) = self.data[i][j] {
                        let new_distance = distances[i] + distance;

                        if new_distance < distances[j] {
                            distances[j] = new_distance;
                        }
                    }
                }
            }
        }

        for _ in 0..self.size - 1 {
            for i in 0..self.size {
                for j in 0..self.size {
                    if let Some(distance) = self.data[i][j] {
                        if distances[i] + distance < distances[j] {
                            distances[j] = isize::MIN;
                        }
                    }
                }
            }
        }

        return distances;
    }

    fn floyd_warshall(&self) -> Vec<Vec<isize>> {
        let mut distances = vec![vec![isize::MAX; self.size]; self.size];

        for i in 0..self.size {
            for j in 0..self.size {
                if let Some(weight) = self.data[i][j] {
                    distances[i][j] = weight;
                }
            }
        }

        for k in 0..self.size {
            for i in 0..self.size {
                for j in 0..self.size {
                    let new_distance: isize;

                    if distances[i][k] != isize::MAX && distances[k][j] != isize::MAX {
                        new_distance = distances[i][k] + distances[k][j];
                    } else {
                        new_distance = isize::MAX;
                    }

                    if new_distance < distances[i][j] {
                        distances[i][j] = new_distance;
                    }
                }
            }
        }

        for k in 0..self.size {
            for i in 0..self.size {
                for j in 0..self.size {
                    if distances[i][k] != isize::MAX
                        && distances[k][j] != isize::MAX
                        && distances[k][k] < 0
                    {
                        distances[i][j] = isize::MIN;
                    }
                }
            }
        }

        return distances;
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

    let mut another_graph = AdjacencyMatrixGraph::new(4);

    another_graph.add_directed_edge(0, 1, 4);
    another_graph.add_directed_edge(0, 2, 5);
    another_graph.add_directed_edge(1, 2, -2);
    another_graph.add_directed_edge(1, 3, 6);
    another_graph.add_directed_edge(2, 3, 1);
    another_graph.add_directed_edge(2, 2, 10);

    println!("Bellman-Ford Algorithm");
    println!("{:?}", another_graph.bellman_ford(0));

    println!("Floyd-Warshall Algorithm");
    for distances in another_graph.floyd_warshall() {
        println!("{:?}", distances);
    }
}
