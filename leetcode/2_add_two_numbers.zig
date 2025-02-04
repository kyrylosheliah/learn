// 2. Add Two Numbers
//
// You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//
// Example 1:
//
// Input: l1 = [2,4,3], l2 = [5,6,4]
// Output: [7,0,8]
// Explanation: 342 + 465 = 807.
//
// Example 2:
//
// Input: l1 = [0], l2 = [0]
// Output: [0]
//
// Example 3:
//
// Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
// Output: [8,9,9,9,0,0,0,1]
//
// Constraints:
//
//     The number of nodes in each linked list is in the range [1, 100].
//     0 <= Node.val <= 9
//     It is guaranteed that the list represents a number that does not have leading zeros.

const std = @import("std");
const TestSuite = @import("test_suite").TestSuite;

const TInput = struct {
    l1: []const usize,
    l2: []const usize,
};

const TOutput = []const usize;

fn printEmAll(x: TOutput, y: TOutput) void {
    std.debug.print("    [ ", .{});
    for (x) |xi| std.debug.print("{d} ", .{xi});
    std.debug.print(" ] ??? [ ", .{});
    for (y) |yi| std.debug.print("{d} ", .{yi});
    std.debug.print(" ]\n", .{});
}

fn Equal(x: TOutput, y: TOutput) bool {
    const pass = blk: {
        if (x.len != y.len) break :blk false;
        for (x, y) |xi, yi| if (xi != yi) break :blk false;
        break :blk true;
    };
    if (!pass) printEmAll(x, y);
    return pass;
}

fn EqualizeInputLengths(arena: *std.heap.ArenaAllocator, x: TInput) !TOutput {
    const allocator = arena.allocator();
    const are_equal = x.l1.len == x.l2.len;
    const l1_is_bigger = x.l1.len > x.l2.len;
    const max_len = if (are_equal or l1_is_bigger) x.l1.len else x.l2.len;
    // maximum theoretical capacity (999 + 99 = 1_098)
    const capacity = max_len + 1;
    var list = try std.ArrayList(usize).initCapacity(allocator, capacity);
    // equalize inputs
    var left = try std.ArrayList(usize).initCapacity(allocator, max_len);
    try left.appendSlice(x.l1);
    var right = try std.ArrayList(usize).initCapacity(allocator, max_len);
    try right.appendSlice(x.l2);
    if (!are_equal) {
        if (l1_is_bigger) {
            try right.appendNTimes(0, max_len - right.items.len);
        } else {
            try left.appendNTimes(0, max_len - left.items.len);
        }
    }
    // solve
    var carry: u8 = 0;
    for (left.items, right.items) |li, ri| {
        const sum = li + ri + carry;
        if (sum > 9) {
            const digit = if (sum > 9) sum - 10 else 0;
            try list.append(digit);
            carry = 1;
        } else {
            carry = 0;
            try list.append(sum);
        }
    }
    // carry shouldn't be greater than 18 at this point
    while (carry > 0) {
        if (carry > 9) {
            carry -= 9;
            try list.append(9);
        } else {
            try list.append(carry);
            //carry = 0;
            break;
        }
    }
    return try list.toOwnedSlice();
}

fn SumThenCarryRemainders(arena: *std.heap.ArenaAllocator, x: TInput) !TOutput {
    const allocator = arena.allocator();
    var sum: usize = 0;
    var power: usize = x.l1.len;
    for (0..x.l1.len) |i| {
        power -= 1;
        sum += std.math.pow(usize, 10, power) * x.l1[i];
    }
    power = x.l2.len;
    for (0..x.l2.len) |i| {
        power -= 1;
        sum += std.math.pow(usize, 10, power) * x.l2[i];
    }
    const l1_is_bigger = x.l1.len > x.l2.len;
    const max_len = if (l1_is_bigger) x.l1.len else x.l2.len;
    // maximum theoretical capacity (999 + 99 = 1_098) == (max_len + 1)
    // then will reverse by appending in reverse order to the end
    const capacity = (max_len + 1) * 2;
    var list = try std.ArrayList(usize).initCapacity(allocator, capacity);
    power = max_len + 1;
    while (power > 0) {
        power -= 1;
        const rank = std.math.pow(usize, 10, power);
        const carry = sum / rank;
        const digit = sum % rank;
        //std.debug.print("{d} {d} {d}\n", .{ rank, carry, digit });
        try list.append(carry);
        sum = digit;
    }
    // the power of 10 could be overshooting
    if (list.items[0] == 0) _ = list.orderedRemove(0);
    // reverse by appending to the same list and slicing the end
    const old_len = list.items.len;
    var i = old_len;
    while (i > 0) {
        i -= 1;
        try list.append(list.items[i]);
    }
    return list.items[old_len..];
}

test "2 add two numbers" {
    var test_suite = TestSuite(TInput, TOutput, Equal).init();
    defer test_suite.deinit();

    try test_suite.inputs.append(.{ .l1 = &.{ 2, 4, 3 }, .l2 = &.{ 5, 6, 4 } });
    try test_suite.outputs.append(&.{ 7, 0, 8 });

    try test_suite.inputs.append(.{ .l1 = &.{0}, .l2 = &.{0} });
    try test_suite.outputs.append(&.{0});

    try test_suite.inputs.append(.{ .l1 = &.{ 9, 9, 9, 9, 9, 9, 9 }, .l2 = &.{ 9, 9, 9, 9 } });
    try test_suite.outputs.append(&.{ 8, 9, 9, 9, 0, 0, 0, 1 });

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &EqualizeInputLengths },
        .{ .run = &SumThenCarryRemainders },
    });

    try test_suite.run();

    try std.testing.expect(!test_suite.result.failed);
}
