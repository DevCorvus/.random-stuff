fn bubble_sort<T: Ord>(arr: &mut [T]) {
    if arr.is_empty() {
        return;
    }

    let mut sorted = false;
    let mut n = arr.len();

    while !sorted {
        sorted = true;
        for i in 0..n - 1 {
            if arr[i] > arr[i + 1] {
                arr.swap(i, i + 1);
                sorted = false;
            }
        }
        n -= 1;
    }
}

pub fn run<T: Ord + Copy>(arr: &[T]) -> Vec<T> {
    let mut arr_copy = arr.to_vec();

    bubble_sort(&mut arr_copy);

    arr_copy
}
