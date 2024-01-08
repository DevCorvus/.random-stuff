use std::cmp::{min, Ordering};
use std::collections::{BinaryHeap, HashMap, VecDeque};
mod min_indexed_d_heap;

const DEPTH_TOKEN: isize = -1;

struct Edge {
    to: usize,
    cost: isize,
}

// Priority Queue node for Dijkstra's algorithm
#[derive(Eq, PartialEq)]
struct Node {
    index: usize,
    cost: usize,
}

impl Ord for Node {
    fn cmp(&self, other: &Self) -> Ordering {
        other
            .cost
            .cmp(&self.cost)
            .then_with(|| self.index.cmp(&other.index))
    }
}

impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

struct AdjacencyListGraph {
    data: HashMap<usize, Vec<Edge>>,
    size: usize,
    edge_count: usize,
}

impl AdjacencyListGraph {
    pub fn new() -> Self {
        Self {
            data: HashMap::new(),
            size: 0,
            edge_count: 0,
        }
    }

    fn add_directed_edge(&mut self, from: usize, to: usize, cost: isize) {
        let edge = Edge { to, cost };

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

        self.edge_count += 1;
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

    fn topological_sort(&self) -> Vec<usize> {
        let mut visited = vec![false; self.size];
        let mut ordering = vec![0; self.size];

        let mut i = self.size - 1;

        for at in 0..self.size {
            if !visited[at] {
                i = self._dfs_topsort(i, at, &mut visited, &mut ordering);
            }
        }

        return ordering;
    }

    fn _dfs_topsort(
        &self,
        mut i: usize,
        at: usize,
        visited: &mut Vec<bool>,
        ordering: &mut Vec<usize>,
    ) -> usize {
        visited[at] = true;

        if let Some(edges) = self.data.get(&at) {
            for edge in edges {
                if !visited[edge.to] {
                    i = self._dfs_topsort(i, edge.to, visited, ordering);
                }
            }
        }

        ordering[i] = at;

        if i > 0 {
            return i - 1;
        } else {
            return i;
        }
    }

    fn dag_shortest_path(&self, start: usize) -> Vec<Option<isize>> {
        let topsorted = self.topological_sort();
        let mut distances = vec![None; self.size];

        distances[start] = Some(0);

        for i in 0..self.size {
            let node_index = topsorted[i];
            if let Some(distance) = distances[node_index] {
                if let Some(edges) = self.data.get(&node_index) {
                    for edge in edges {
                        let new_distance = distance + edge.cost;

                        match distances[edge.to] {
                            Some(next_distance) => {
                                distances[edge.to] = Some(min(next_distance, new_distance));
                            }
                            None => {
                                distances[edge.to] = Some(new_distance);
                            }
                        }
                    }
                }
            }
        }

        return distances;
    }

    // Just like finding the shortest path but costs are negative
    fn dag_longest_path(&self, start: usize) -> Vec<Option<isize>> {
        let topsorted = self.topological_sort();
        let mut distances = vec![None; self.size];

        distances[start] = Some(0);

        for i in 0..self.size {
            let node_index = topsorted[i];
            if let Some(distance) = distances[node_index] {
                if let Some(edges) = self.data.get(&node_index) {
                    for edge in edges {
                        let new_distance = distance + (edge.cost * -1);

                        match distances[edge.to] {
                            Some(next_distance) => {
                                distances[edge.to] = Some(min(next_distance, new_distance));
                            }
                            None => {
                                distances[edge.to] = Some(new_distance);
                            }
                        }
                    }
                }
            }
        }

        return distances
            .into_iter()
            .flatten()
            .map(|distance| Some(distance * -1))
            .collect();
    }

    fn lazy_dijkstra(&self, start: usize, end: usize) -> Option<(usize, Vec<usize>)> {
        let mut distances = vec![usize::MAX; self.size];
        distances[start] = 0;

        let mut priority_queue = BinaryHeap::new(); // Priority Queue
        priority_queue.push(Node {
            index: start,
            cost: 0,
        });

        let mut visited = vec![false; self.size];
        visited[start] = true;

        // Useful to reconstruct the path
        let mut prev = vec![None; self.size];

        while let Some(Node { index, cost }) = priority_queue.pop() {
            visited[index] = true;
            if cost > distances[index] {
                continue;
            }

            if let Some(edges) = self.data.get(&index) {
                for edge in edges {
                    if visited[edge.to] {
                        continue;
                    }

                    let next = Node {
                        index: edge.to,
                        cost: cost + edge.cost as usize,
                    };

                    if next.cost < distances[next.index] {
                        prev[edge.to] = Some(index);
                        distances[next.index] = next.cost;
                        priority_queue.push(next);
                    }
                }
            }

            if index == end {
                return Some((
                    distances[end],
                    self._reconstruct_path(start, end, prev).unwrap(),
                ));
            }
        }

        return None;
    }

    fn eager_dijkstra_with_dary_optimization(
        &self,
        start: usize,
        end: usize,
    ) -> Option<(usize, Vec<usize>)> {
        let degree: usize = self.edge_count / self.size;

        let mut dary_indexed_priority_queue: min_indexed_d_heap::MinIndexedDHeap<usize> =
            min_indexed_d_heap::MinIndexedDHeap::new(degree, self.size);

        dary_indexed_priority_queue.insert(start, 0);

        let mut distances = vec![usize::MAX; self.size];
        distances[start] = 0;

        let mut visited = vec![false; self.size];

        // Useful to reconstruct the path
        let mut prev = vec![None; self.size];

        while let Some(min_index) = dary_indexed_priority_queue.peek_min_key_index() {
            visited[min_index] = true;

            let min_value = dary_indexed_priority_queue.poll_min_value().unwrap();

            if min_value > distances[min_index] {
                continue;
            }

            if let Some(edges) = self.data.get(&min_index) {
                for edge in edges {
                    if visited[edge.to] {
                        continue;
                    }

                    let new_distance = distances[min_index] + edge.cost as usize;

                    if new_distance < distances[edge.to] {
                        prev[edge.to] = Some(min_index);
                        distances[edge.to] = new_distance;

                        if !dary_indexed_priority_queue.contains(edge.to) {
                            dary_indexed_priority_queue.insert(edge.to, new_distance);
                        } else {
                            dary_indexed_priority_queue.decrease(edge.to, new_distance);
                        }
                    }
                }
            }

            if min_index == end {
                return Some((
                    distances[end],
                    self._reconstruct_path(start, end, prev).unwrap(),
                ));
            }
        }

        return None;
    }

    fn bellman_ford(&self, start: usize) -> Vec<isize> {
        let mut distances = vec![isize::MAX; self.size];
        distances[start] = 0;

        for (node, edges) in self.data.iter() {
            for edge in edges {
                let new_distance = distances[*node] + edge.cost;

                if new_distance < distances[edge.to] {
                    distances[edge.to] = new_distance;
                }
            }
        }

        // Find negative cycles
        for (node, edges) in self.data.iter() {
            for edge in edges {
                if distances[*node] + edge.cost < distances[edge.to] {
                    distances[edge.to] = isize::MIN;
                }
            }
        }

        return distances;
    }
}

fn main() {
    let mut graph = AdjacencyListGraph::new();

    graph.add_directed_edge(0, 1, 4);
    graph.add_directed_edge(0, 2, 5);
    // graph.add_directed_edge(1, 2, -2);
    graph.add_directed_edge(1, 2, 2);
    graph.add_directed_edge(1, 3, 6);
    graph.add_directed_edge(2, 3, 1);
    // graph.add_directed_edge(2, 2, 10);

    assert_eq!(graph.size, 4);

    assert_eq!(graph.depth_first_search(0), 4);
    assert_eq!(graph.depth_first_search(3), 1);

    assert_eq!(graph.depth_first_search_recursive(0), 4);
    assert_eq!(graph.depth_first_search_recursive(3), 1);

    assert_eq!(graph.topological_sort(), [0, 1, 2, 3]);

    assert_eq!(
        graph.dag_shortest_path(1),
        [None, Some(0), Some(2), Some(3)]
    );

    assert_eq!(
        graph.dag_longest_path(0),
        [Some(0), Some(4), Some(6), Some(10)]
    );

    assert_eq!(graph.lazy_dijkstra(0, 3), Some((6, vec![0, 2, 3])));

    assert_eq!(
        graph.eager_dijkstra_with_dary_optimization(0, 3),
        Some((6, vec![0, 2, 3]))
    );

    assert_eq!(graph.bellman_ford(0), vec![0, 4, 5, 6]);

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
