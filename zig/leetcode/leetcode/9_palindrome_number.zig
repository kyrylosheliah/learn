// 9. Palindrome Number
// 
// Given an integer x, return true if x is a
// palindrome
// , and false otherwise.
// 
//  
// 
// Example 1:
// 
// Input: x = 121
// Output: true
// Explanation: 121 reads as 121 from left to right and from right to left.
// 
// Example 2:
// 
// Input: x = -121
// Output: false
// Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
// 
// Example 3:
// 
// Input: x = 10
// Output: false
// Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
// 
//  
// 
// Constraints:
// 
//     -2^31 <= x <= 2^31 - 1
// 
//  
// Follow up: Could you solve it without converting the integer to a string?

const std = @import("std");
const print = std.debug.print;
const TestSuite = @import("test_suite").TestSuite;

const TInput = i32;

const TOutput = bool;

fn equalBool(x: TOutput, y: TOutput) bool {
    return x == y;
}

fn reverseThenCompare(alloc: *std.mem.Allocator, x: TInput) !TOutput {
    _ = alloc;
    if (x < 0) return false;
    var integer = x;
    var reversed: TInput = 0;
    while (integer != 0) {
        const last_digit = @rem(integer, 10);
        reversed = reversed * 10 + last_digit;
        integer = @divTrunc(integer, 10);
    }
    return x == reversed;
}

test "9" {
    var test_suite = TestSuite(TInput, TOutput, equalBool, "palindrome number").init();
    defer test_suite.deinit();

    try test_suite.inputs.append(121);
    try test_suite.outputs.append(true);

    try test_suite.inputs.append(-121);
    try test_suite.outputs.append(false);

    try test_suite.inputs.append(10);
    try test_suite.outputs.append(false);

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &reverseThenCompare },
    });

    try test_suite.run();

    try std.testing.expect(test_suite.pass);
}