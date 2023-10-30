void main(List<String> args) {
  var fruits = ["Apple", "Banana", "Pear"];

  var index = 0;
  while (index < fruits.length) {
    print(fruits[index]);
    index++;
  }

  for (var i = 0; i < fruits.length; i++) {
    print(fruits[i]);
  }

  for (final fruit in fruits) {
    print(fruit);
  }

  fruits.forEach((e) => print(e));
}
