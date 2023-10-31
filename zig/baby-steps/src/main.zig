const std = @import("std");
const print = std.debug.print;

pub fn add(n1: f64, n2: f64) f64 {
    return n1 + n2;
}

pub fn fib(n: usize) usize {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

pub fn main() !void {
    print("Hello World\n", .{});

    var result: ?f64 = null;
    print("Result: {?}\n", .{result});
    result = add(4, 4);
    print("Result: {?}\n", .{result});

    print("Fib: {}\n", .{fib(40)});
}
