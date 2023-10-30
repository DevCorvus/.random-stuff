package com.mycompany.app;

public class Store {
    private Person[] people;
    private int count;

    public Store(int cap) {
        people = new Person[cap];
        count = 0;
    }

    public void create(String name, int age) {
        people[count + 1] = new Person(count + 1, name, age);
        count++;
    }

    public Person[] getAll() {
        return people;
    }

    public Person get(int id) {
        return people[id];
    }

    public void update(int id, String name, int age) {
        people[id].setName(name);
        people[id].setAge(age);
    }

    public void delete(int id) {
        people[id] = null;
        count--;
    }
}
