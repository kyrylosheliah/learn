// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

// You may assume that each input would have exactly one solution, and you may not use the same element twice.

// You can return the answer in any order.

// Example 1:

// Input: nums = [2,7,11,15], target = 9
// Output: [0,1]
// Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

// Example 2:

// Input: nums = [3,2,4], target = 6
// Output: [1,2]

// Example 3:

// Input: nums = [3,3], target = 6
// Output: [0,1]

// Constraints:

//    2 <= nums.length <= 10^4
//    -10^9 <= nums[i] <= 10^9
//    -10^9 <= target <= 10^9
//    Only one valid answer exists.

const std = @import("std");
const TestSuite = @import("../test_suite.zig").TestSuite;

const TInput = struct {
    nums: []const i32,
    target: i32,
};

const TOutput = []const i32;

fn Equal(x: TOutput, y: TOutput) bool {
    for (x, y) |xi, yi| if (xi != yi) return false;
    return true;
}

fn CombinationsPyramid(allocator: std.mem.Allocator, x: TInput) !TOutput {
    _ = &allocator;
    const len = x.nums.len;
    for (1..len) |gap| {
        for (gap..len) |right| {
            const left = right - gap;
            if (x.nums[left] + x.nums[right] == x.target) {
                const static_result = struct {
                    var arr = [2]i32{ 0, 0 };
                };
                static_result.arr[0] = @intCast(left);
                static_result.arr[1] = @intCast(right);
                return &static_result.arr;
            }
        }
    }
    return &.{};
}

test "1. Two sum" {
    const allocator = std.testing.allocator;

    var test_suite = TestSuite(
        TInput,
        TOutput,
        Equal,
    ).init(allocator);
    defer test_suite.deinit();

    try test_suite.inputs.append(.{ .nums = &.{ 2, 7, 11, 15 }, .target = 9 });
    try test_suite.outputs.append(&.{ 0, 1 });

    try test_suite.inputs.append(.{ .nums = &.{ 3, 2, 4 }, .target = 6 });
    try test_suite.outputs.append(&.{ 1, 2 });

    try test_suite.inputs.append(.{ .nums = &.{ 3, 3 }, .target = 6 });
    try test_suite.outputs.append(&.{ 0, 1 });

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &CombinationsPyramid },
    });

    try test_suite.run();

    try std.testing.expect(!test_suite.result.failed);
}