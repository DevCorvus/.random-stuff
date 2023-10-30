class Person(val name: String, val age: Int) {
  fun sayHi() {
    println("Hi! my name is $name");
  }

  fun sayAge() {
    println("I'm $age years old");
  }
}

fun main() {
  val person = mapOf("name" to "Luis", "age" to 21);
  println(person);
  println(person["name"]);

  val personInstance = Person("Luis", 21);
  personInstance.sayHi();
  personInstance.sayAge();
}
