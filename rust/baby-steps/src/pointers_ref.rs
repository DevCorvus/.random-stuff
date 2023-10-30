pub fn run() {
  // Primitive Array
  let arr1 = [1, 2, 3];
  let arr2 = arr1;
  // Vectors
  let vec1 = vec![1, 2, 3];
  let vec2 = &vec1;
  
  println!("Array values: {:?}", (arr1, arr2));
  println!("Vector values: {:?}", (&vec1, vec2));
}