import 'dart:collection';

import 'package:http/http.dart' as http;

void main(List<String> args) async {
  // String url = "https://jsonplaceholder.typicode.com/users";
  var url = Uri.https("jsonplaceholder.typicode.com", "/users");

  Map<String, String> headers = new HashMap();
  headers.putIfAbsent('Accept', () => 'application/json');

  http.Response res = await http.get(url, headers: headers);

  print(res.body);
}
