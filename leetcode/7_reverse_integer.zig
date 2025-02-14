// 7. Reverse Integer
// 
// Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], then return 0.
// 
// Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
// 
// Example 1:
// 
// Input: x = 123
// Output: 321
// 
// Example 2:
// 
// Input: x = -123
// Output: -321
// 
// Example 3:
// 
// Input: x = 120
// Output: 21
// 
// Constraints:
// 
//     -2^31 <= x <= 2^31 - 1

const std = @import("std");
const print = std.debug.print;
const TestSuite = @import("test_suite").TestSuite;

const TInput = isize;

const TOutput = isize;

fn equalInteger(x: TInput, y: TOutput) bool {
    print("{d} ?? {d}\n", .{x, y});
    return x == y;
}

fn try1(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    _ = alloc;
    var integer = x;
    const upper_limit: isize = @divTrunc(std.math.maxInt(TInput), 10);
    const lower_limit: isize = @divTrunc(std.math.minInt(TInput), 10);
    var ans: isize = 0;
    while (integer != 0) {
        const last_digit = @rem(integer, 10);
        ans = ans * 10 + last_digit;
        if (ans > upper_limit or (ans == upper_limit and last_digit > 7)) return 0;
        if (ans < lower_limit or (ans == lower_limit and last_digit < -8)) return 0;
        integer = @divTrunc(integer, 10);
    }
    return ans;
}

test "7" {
    var test_suite = TestSuite(TInput, TOutput, equalInteger, "reverse integer").init();
    defer test_suite.deinit();

    try test_suite.inputs.append(123);
    try test_suite.outputs.append(321);

    try test_suite.inputs.append(-123);
    try test_suite.outputs.append(-321);

    try test_suite.inputs.append(120);
    try test_suite.outputs.append(21);

    try test_suite.inputs.append(12000000);
    try test_suite.outputs.append(21);

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &try1 },
    });

    try test_suite.run();

    try std.testing.expect(test_suite.pass);
}