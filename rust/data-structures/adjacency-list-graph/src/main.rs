mod iterative;
mod recursive;

fn main() {
    let mut igraph = iterative::AdjacencyListGraph::new();

    igraph.add(0, 1, 4);
    igraph.add(0, 2, 5);
    igraph.add(1, 2, -2);
    igraph.add(1, 3, 6);
    igraph.add(2, 3, 1);
    igraph.add(2, 2, 10);

    assert_eq!(igraph.depth_first_search(0), 4);
    assert_eq!(igraph.depth_first_search(4), 1);

    let mut rgraph = recursive::AdjacencyListGraph::new();

    rgraph.add(0, 1, 4);
    rgraph.add(0, 2, 5);
    rgraph.add(1, 2, -2);
    rgraph.add(1, 3, 6);
    rgraph.add(2, 3, 1);
    rgraph.add(2, 2, 10);

    assert_eq!(rgraph.depth_first_search(0), 4);
    assert_eq!(rgraph.depth_first_search(4), 1);
}
