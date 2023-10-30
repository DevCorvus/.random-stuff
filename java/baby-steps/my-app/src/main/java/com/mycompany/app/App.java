package com.mycompany.app;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

/**
 * Hello world!
 *
 */
public class App {
    public static void main(String[] args) {
        String message = "Illo";
        System.out.println(message);

        Store myStore = new Store(10);
        myStore.create("Luis", 21);
        myStore.create("Fulana", 20);
        myStore.create("Mariano", 22);

        Person fulana = myStore.get(2);
        System.out.println(fulana.getName());
        myStore.update(3, "Canguro", 22);
        myStore.delete(1);

        Person[] people = myStore.getAll();
        for (Person person : people) {
            if (person != null) {
                System.out.println(person.getName());
            }
        }

        String filename = "document.txt";

        File myFile = new File(filename);
        try {
            if (!myFile.exists()) {
                boolean fileCreated = myFile.createNewFile();
                if (fileCreated) {
                    FileWriter myWriter = new FileWriter(filename);
                    myWriter.write("uwu content");
                    myWriter.close();
                    System.out.println("Successful file writing");
                }
            } else {
                FileWriter myWriter = new FileWriter(filename, true);
                BufferedWriter myBufferedWriter = new BufferedWriter(myWriter);
                myBufferedWriter.newLine();
                myBufferedWriter.append("more uwu content");
                myBufferedWriter.close();
                System.out.println("Successful file update");
            }
        } catch (IOException e) {
            System.out.println(e);
        }

        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest
                .newBuilder(
                        URI.create("https://jsonplaceholder.typicode.com/posts/1"))
                .build();

        try {
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            System.out.println(response.body());

        } catch (InterruptedException e) {
            System.out.println(e);
        } catch (IOException e) {
            System.out.println(e);
        }
    }
}
