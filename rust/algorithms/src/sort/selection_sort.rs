pub fn selection_sort<T: Ord>(arr: &mut [T]) {
    let len = arr.len();
    for left in 0..len {
        let mut smallest = left;
        for right in (left + 1)..len {
            if arr[right] < arr[smallest] {
                smallest = right;
            }
        }
        arr.swap(smallest, left);
    }
}

pub fn run<T: Ord + Copy>(arr: &[T]) -> Vec<T> {
    let mut arr_copy = arr.to_vec();

    selection_sort(&mut arr_copy);

    arr_copy
}
