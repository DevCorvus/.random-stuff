class Person {
  String name;
  int age;

  Person(this.name, this.age) {}

  sayHi() {
    print("Hi! my name is $name");
  }
}

void main(List<String> args) {
  var person = {
    "name": "Luis",
    "age": 21,
  };
  print(person);
  print(person["name"]);

  var personInstance = new Person("Luis", 21);
  personInstance.sayHi();
}
