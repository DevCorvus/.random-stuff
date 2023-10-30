fn insertion_sort<T: Ord + Copy>(arr: &mut [T]) {
    for i in 1..arr.len() {
        let mut j = i;
        let current = arr[i];

        while j > 0 && current < arr[j - 1] {
            arr[j] = arr[j - 1];
            j -= 1;
        }

        arr[j] = current;
    }
}

pub fn run<T: Ord + Copy>(arr: &[T]) -> Vec<T> {
    let mut arr_copy = arr.to_vec();

    insertion_sort(&mut arr_copy);

    arr_copy
}
