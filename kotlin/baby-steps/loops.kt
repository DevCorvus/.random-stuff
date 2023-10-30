fun main() {
  val fruits = listOf("Apple", "Banana", "Pear");

  var i = 0;
  while (i < fruits.size) {
    println(fruits[i]);
    i++;
  }

  for (fruit in fruits) {
    println(fruit);
  }
}