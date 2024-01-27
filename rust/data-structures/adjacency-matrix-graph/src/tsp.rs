pub struct TravelingSalesmanRecursive {
    distances: Vec<Vec<usize>>,
    size: usize,
    start: usize,
    end_state: usize,
}

impl TravelingSalesmanRecursive {
    pub fn new(start: usize, distances: Vec<Vec<usize>>) -> Self {
        let size = distances.len();

        Self {
            distances,
            size,
            start,
            end_state: (1 << size) - 1,
        }
    }

    pub fn solve(&self) -> (Vec<usize>, usize) {
        let mut state = 1 << self.start;

        let memo = &mut vec![vec![None; 1 << self.size]; self.size];
        let prev = &mut vec![vec![None; 1 << self.size]; self.size];

        let min_tour_cost = self.tsp(self.start, state, memo, prev);
        let mut tour = Vec::new();

        let mut index = self.start;
        loop {
            tour.push(index);
            match prev[index][state] {
                None => {
                    break;
                }
                Some(next_index) => {
                    let next_state = state | (1 << next_index);
                    state = next_state;
                    index = next_index;
                }
            }
        }

        tour.push(self.start);

        return (tour, min_tour_cost);
    }

    fn tsp(
        &self,
        i: usize,
        state: usize,
        memo: &mut Vec<Vec<Option<usize>>>,
        prev: &mut Vec<Vec<Option<usize>>>,
    ) -> usize {
        if state == self.end_state {
            return self.distances[i][self.start];
        }

        if let Some(v) = memo[i][state] {
            return v;
        }

        let mut min_cost = usize::MAX;

        let mut index = None;
        for next in 0..self.size {
            if state & (1 << next) != 0 {
                continue;
            }

            let next_state = state | (1 << next);
            let new_cost = self.distances[i][next] + self.tsp(next, next_state, memo, prev);

            if new_cost < min_cost {
                min_cost = new_cost;
                index = Some(next);
            }
        }

        prev[i][state] = index;
        memo[i][state] = Some(min_cost);

        return min_cost;
    }
}
