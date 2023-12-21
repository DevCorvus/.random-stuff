use std::collections::{HashMap, VecDeque};

const DEPTH_TOKEN: isize = -1;

struct Edge {
    #[allow(unused)]
    from: usize,
    to: usize,
    #[allow(unused)]
    cost: isize,
}

struct AdjacencyListGraph {
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

    fn add_directed_edge(&mut self, from: usize, to: usize, cost: isize) {
        let edge = Edge { from, to, cost };

        if self.data.get(&from).is_none() {
            self.data.insert(from, Vec::new());
            self.size += 1;
        }

        if self.data.get(&to).is_none() {
            self.data.insert(to, Vec::new());
            self.size += 1;
        }

        let edges = self.data.get_mut(&from).unwrap();
        edges.push(edge);
    }

    fn add_undirected_edge(&mut self, from: usize, to: usize, cost: isize) {
        self.add_directed_edge(from, to, cost);
        self.add_directed_edge(to, from, cost);
    }

    fn add_unweighted_undirected_edge(&mut self, from: usize, to: usize) {
        self.add_undirected_edge(from, to, 1);
    }

    fn depth_first_search(&self, start: usize) -> usize {
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

    fn depth_first_search_recursive(&self, at: usize) -> usize {
        let mut visited = vec![false; self.size];
        return self._depth_first_search_recursive(at, &mut visited);
    }

    fn _depth_first_search_recursive(&self, at: usize, visited: &mut Vec<bool>) -> usize {
        if visited[at] {
            return 0;
        }

        visited[at] = true;
        let mut count: usize = 1;

        if let Some(edges) = self.data.get(&at) {
            for edge in edges {
                count += self._depth_first_search_recursive(edge.to, visited);
            }
        }

        return count;
    }

    fn reconstruct_path_with_bfs(&self, start: usize, end: usize) -> Option<Vec<usize>> {
        let prev = self._breadth_first_search(start);
        let path = self._reconstruct_path(start, end, prev);
        return path;
    }

    fn _breadth_first_search(&self, start: usize) -> Vec<Option<usize>> {
        let mut queue: VecDeque<usize> = VecDeque::new();
        queue.push_back(start);

        let mut visited = vec![false; self.size];
        visited[start] = true;

        let mut prev: Vec<Option<usize>> = vec![None; self.size];

        while let Some(i) = queue.pop_front() {
            if let Some(edges) = self.data.get(&i) {
                for edge in edges {
                    if !visited[edge.to] {
                        visited[edge.to] = true;
                        prev[edge.to] = Some(i);
                        queue.push_back(edge.to);
                    }
                }
            }
        }

        return prev;
    }

    fn _reconstruct_path(
        &self,
        start: usize,
        end: usize,
        prev: Vec<Option<usize>>,
    ) -> Option<Vec<usize>> {
        let mut path = Vec::new();

        let mut at = Some(end);
        while let Some(v) = at {
            path.push(v);
            at = prev[v];
        }

        path.reverse();

        if path[0] == start {
            return Some(path);
        } else {
            return None;
        }
    }

    fn breadth_first_search_recursive(&self, start: usize) -> usize {
        let mut visited = vec![false; self.size];

        let mut queue: VecDeque<isize> = VecDeque::new();
        queue.push_back(start as isize);
        queue.push_back(DEPTH_TOKEN);

        return self._breadth_first_search_recursive(&mut visited, &mut queue);
    }

    fn _breadth_first_search_recursive(
        &self,
        visited: &mut Vec<bool>,
        queue: &mut VecDeque<isize>,
    ) -> usize {
        let at = queue.pop_front().unwrap();

        if at == DEPTH_TOKEN {
            queue.push_back(DEPTH_TOKEN);
            return 1;
        }

        let at: usize = at as usize;

        if visited[at] {
            return 0;
        }

        visited[at] = true;

        if let Some(neighbours) = self.data.get(&at) {
            for next in neighbours {
                if !visited[next.to] {
                    queue.push_back(next.to as isize);
                }
            }
        }

        let mut depth: usize = 0;

        while queue.len() != 1 || *queue.front().unwrap() != DEPTH_TOKEN {
            depth += self._breadth_first_search_recursive(visited, queue);
        }

        return depth;
    }
}

fn main() {
    let mut graph = AdjacencyListGraph::new();

    graph.add_directed_edge(0, 1, 4);
    graph.add_directed_edge(0, 2, 5);
    graph.add_directed_edge(1, 2, -2);
    graph.add_directed_edge(1, 3, 6);
    graph.add_directed_edge(2, 3, 1);
    graph.add_directed_edge(2, 2, 10);

    assert_eq!(graph.size, 4);

    assert_eq!(graph.depth_first_search(0), 4);
    assert_eq!(graph.depth_first_search(3), 1);

    assert_eq!(graph.depth_first_search_recursive(0), 4);
    assert_eq!(graph.depth_first_search_recursive(3), 1);

    let mut another_graph = AdjacencyListGraph::new();

    another_graph.add_unweighted_undirected_edge(0, 7);
    another_graph.add_unweighted_undirected_edge(0, 9);
    another_graph.add_unweighted_undirected_edge(0, 11);
    another_graph.add_unweighted_undirected_edge(7, 11);
    another_graph.add_unweighted_undirected_edge(7, 6);
    another_graph.add_unweighted_undirected_edge(7, 3);
    another_graph.add_unweighted_undirected_edge(6, 5);
    another_graph.add_unweighted_undirected_edge(3, 4);
    another_graph.add_unweighted_undirected_edge(2, 3);
    another_graph.add_unweighted_undirected_edge(2, 12);
    another_graph.add_unweighted_undirected_edge(12, 8);
    another_graph.add_unweighted_undirected_edge(8, 1);
    another_graph.add_unweighted_undirected_edge(1, 10);
    another_graph.add_unweighted_undirected_edge(10, 9);
    another_graph.add_unweighted_undirected_edge(9, 8);

    assert_eq!(another_graph.size, 13);

    assert_eq!(
        another_graph.reconstruct_path_with_bfs(10, 5),
        Some(vec![10, 9, 0, 7, 6, 5])
    );

    let mut another_another_graph = AdjacencyListGraph::new();

    another_another_graph.add_unweighted_undirected_edge(0, 1);
    another_another_graph.add_unweighted_undirected_edge(0, 2);
    another_another_graph.add_unweighted_undirected_edge(0, 3);
    another_another_graph.add_unweighted_undirected_edge(2, 9);
    another_another_graph.add_unweighted_undirected_edge(8, 2);
    another_another_graph.add_unweighted_undirected_edge(3, 4);
    another_another_graph.add_unweighted_undirected_edge(10, 11);
    another_another_graph.add_unweighted_undirected_edge(12, 13);
    another_another_graph.add_unweighted_undirected_edge(3, 5);
    another_another_graph.add_unweighted_undirected_edge(5, 7);
    another_another_graph.add_unweighted_undirected_edge(5, 6);
    another_another_graph.add_unweighted_undirected_edge(0, 10);
    another_another_graph.add_unweighted_undirected_edge(11, 12);

    assert_eq!(another_another_graph.size, 14);

    another_another_graph.breadth_first_search_recursive(12);
}
