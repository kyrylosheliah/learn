const std = @import("std");
const TestSuite = @import("test_suite.zig").TestSuite;

fn Equal_i32(x: i32, y: i32) bool {
    return x == y;
}

fn Sum(allocator: std.mem.Allocator, x: []const i32) !i32 {
    _ = &allocator;
    var sum: i32 = 0;
    for (x) |val| {
        sum += val;
    }
    return sum;
}

test "sum" {
    const allocator = std.testing.allocator;

    var test_suite = TestSuite(
        []const i32,
        i32,
        Equal_i32,
    ).init(allocator);
    defer test_suite.deinit();

    try test_suite.inputs.append(&.{ 1, 2, 3, 4 });
    try test_suite.outputs.append(10);

    try test_suite.inputs.append(&.{ 2, 3, 4, 5 });
    try test_suite.outputs.append(14);

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &Sum },
        .{ .run = &Sum },
    });

    try test_suite.run();

    try std.testing.expect(!test_suite.result.failed);
}

fn Factorial(allocator: std.mem.Allocator, x: i32) !i32 {
    _ = &allocator;
    if (x == 0) {
        return 1;
    } else if (x < 0) {
        unreachable;
    }
    var res: i32 = 1;
    var i: i32 = x;
    while (i > 0) {
        res *= i;
        i -= 1;
    }
    return res;
}

test "factorial" {
    const allocator = std.testing.allocator;

    var test_suite = TestSuite(
        i32,
        i32,
        Equal_i32,
    ).init(allocator);
    defer test_suite.deinit();

    try test_suite.inputs.appendSlice(&.{ 1, 2, 3, 4, 5, 6 });
    try test_suite.outputs.appendSlice(&.{ 1, 2, 6, 24, 120, 720 });

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &Factorial },
        .{ .run = &Factorial },
    });

    try test_suite.run();

    try std.testing.expect(!test_suite.result.failed);
}
