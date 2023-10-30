fn merge<T: Ord + Copy>(arr: &mut [T], mid: usize) {
    let left_half = arr[..mid].to_vec();
    let right_half = arr[mid..].to_vec();

    let mut l = 0;
    let mut r = 0;

    for v in arr {
        if r == right_half.len() || (l < left_half.len() && left_half[l] < right_half[r]) {
            *v = left_half[l];
            l += 1;
        } else {
            *v = right_half[r];
            r += 1;
        }
    }
}

fn top_down_merge_sort<T: Ord + Copy>(arr: &mut [T]) {
    if arr.len() > 1 {
        let mid = arr.len() / 2;
        top_down_merge_sort(&mut arr[..mid]);
        top_down_merge_sort(&mut arr[mid..]);
        merge(arr, mid);
    }
}

pub fn run<T: Ord + Copy>(arr: &[T]) -> Vec<T> {
    let mut arr_copy = arr.to_vec();

    top_down_merge_sort(&mut arr_copy);

    return arr_copy;
}
