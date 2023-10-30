use algorithms::sort;

fn main() {
    let list = vec!["d", "a", "c", "b", "e"];

    let list_bubble_sort = sort::bubble_sort::run(&list);
    println!("Bubble sort: {:?}", list_bubble_sort);

    let list_insertion_sort = sort::insertion_sort::run(&list);
    println!("Insertion sort: {:?}", list_insertion_sort);

    let list_selection_sort = sort::selection_sort::run(&list);
    println!("Selection sort: {:?}", list_selection_sort);

    let list_merge_sort = sort::merge_sort::run(&list);
    println!("Merge sort: {:?}", list_merge_sort);

    let list_quick_sort = sort::quick_sort::run(&list);
    println!("Quick sort: {:?}", list_quick_sort);

    let numbers_list = vec![4, 6, 3, 5, 7, 2, 9, 1];

    let list_radix_sort = sort::radix_sort::run(&numbers_list);
    println!("Radix sort: {:?}", list_radix_sort);
}
