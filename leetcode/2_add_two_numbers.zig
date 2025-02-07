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

const TInput_Array = struct {
    l1: []const usize,
    l2: []const usize,
};

const TOutput_Array = []const usize;

fn printEmAll(x: TOutput_Array, y: TOutput_Array) void {
    std.debug.print("    [ ", .{});
    for (x) |xi| std.debug.print("{d} ", .{xi});
    std.debug.print(" ] ??? [ ", .{});
    for (y) |yi| std.debug.print("{d} ", .{yi});
    std.debug.print(" ]\n", .{});
}

fn Equal_Array(x: TOutput_Array, y: TOutput_Array) bool {
    const pass = blk: {
        if (x.len != y.len) break :blk false;
        for (x, y) |xi, yi| if (xi != yi) break :blk false;
        break :blk true;
    };
    if (!pass) printEmAll(x, y);
    return pass;
}

fn EqualizeInputLengths_Array(arena: *std.heap.ArenaAllocator, x: TInput_Array) !TOutput_Array {
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

fn SumThenCarryRemainders_Array(arena: *std.heap.ArenaAllocator, x: TInput_Array) !TOutput_Array {
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
        const digit = sum / rank;
        const remainder = sum % rank;
        //std.debug.print("{d} {d} {d}\n", .{ rank, digit, remainder });
        try list.append(digit);
        sum = remainder;
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

test "2 add two number arrays" {
    var test_suite = TestSuite(TInput_Array, TOutput_Array, Equal_Array, "add arrays").init();
    defer test_suite.deinit();

    try test_suite.inputs.append(.{ .l1 = &.{ 2, 4, 3 }, .l2 = &.{ 5, 6, 4 } });
    try test_suite.outputs.append(&.{ 7, 0, 8 });

    try test_suite.inputs.append(.{ .l1 = &.{0}, .l2 = &.{0} });
    try test_suite.outputs.append(&.{0});

    try test_suite.inputs.append(.{ .l1 = &.{ 9, 9, 9, 9, 9, 9, 9 }, .l2 = &.{ 9, 9, 9, 9 } });
    try test_suite.outputs.append(&.{ 8, 9, 9, 9, 0, 0, 0, 1 });

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &EqualizeInputLengths_Array },
        .{ .run = &SumThenCarryRemainders_Array },
    });

    try test_suite.run();

    try std.testing.expect(!test_suite.result.failed);
}

fn printList(x: TOutput_List) void {
    var current: *ListNode = x;
    std.debug.print("[ ", .{});
    while (current.next != null) {
        std.debug.print("{d}, ", .{ current.val });
        current = current.next.?;
    }
    std.debug.print("{d} ]\n", .{ current.val });
}

fn equalList(x: TOutput_List, y: TOutput_List) bool {
    var left = x;
    var right = y;
    const pass = blk: {
        while (true) {
            if (left.next == null and right.next == null) break :blk true;
            if (left.next == null and right.next != null) break :blk false;
            if (left.next != null and right.next == null) break :blk false;
            if (left.val != right.val) break :blk false;
            left = left.next.?;
            right = right.next.?;
        }
        break :blk true;
    };
    if (!pass) {
        printList(x);
        printList(y);
    }
    return pass;
}

const ListNode = struct {
    val: i32,
    next: ?*ListNode,
};

fn initList(alloc: std.mem.Allocator, arr: []const i32) !*ListNode {
    if (arr.len == 0) unreachable;
    const head: *ListNode = try alloc.create(ListNode);
    head.* = ListNode{ .val = arr[0], .next = null };
    if (arr.len == 1) return head;
    var current: *ListNode = head;
    for (1..arr.len) |i| {
        const new = try alloc.create(ListNode);
        new.* = ListNode{ .val = arr[i], .next = null };
        current.next = new;
        current = new;
    }
    return head;
}

fn appendList(alloc: std.mem.Allocator, node: *ListNode, val: i32) !*ListNode {
    const new = try alloc.create(ListNode);
    new.* = ListNode{ .val = val, .next = null };
    node.next = new;
    return new;
}

const TInput_List = struct {
    l1: *ListNode,
    l2: *ListNode,
};

const TOutput_List = *ListNode;

fn equalizeInputLengths_List(arena: *std.heap.ArenaAllocator, x: TInput_List) !TOutput_List {
    const alloc = arena.allocator();
    var left = x.l1;
    var right = x.l2;
    while (left.next != null and right.next != null) {
        left = left.next.?;
        right = right.next.?;
    }
    if (left.next == null and right.next == null) {
        // equal len
    } else if (left.next == null) {
        while (right.next) |right_next| {
            left = try appendList(alloc, left, 0);
            right = right_next;
        }
    } else if (right.next == null) {
        while (left.next) |left_next| {
            left = left_next;
            right = try appendList(alloc, right, 0);
        }
    }
    // solve
    var carry: i32 = 0;
    const head = try alloc.create(ListNode);
    head.* = ListNode{ .val = 0, .next = null };
    var list = head;
    left = x.l1;
    right = x.l2;
    while (true) {
        const sum = left.val + right.val + carry;
        if (sum > 9) {
            const digit = if (sum > 9) (sum - 10) else 0;
            list = try appendList(alloc, list, digit);
            carry = 1;
        } else {
            carry = 0;
            list = try appendList(alloc, list, sum);
        }
        if (left.next == null or right.next == null) break;
        left = left.next.?;
        right = right.next.?;
    }
    // carry shouldn't be greater than 18 at this point
    while (carry > 0) {
        if (carry > 9) {
            carry -= 9;
            list = try appendList(alloc, list, 9);
        } else {
            list = try appendList(alloc, list, carry);
            //carry = 0;
            break;
        }
    }
    return head.next.?;
}

fn sumList(x: *ListNode) [2]i32 {
    var current = x;
    var len: i32 = 1;
    while (current.next != null) {
        len += 1;
        current = current.next.?;
    }
    var sum: i32 = 0;
    const power: i32 = len - 1;
    var rank = std.math.pow(i32, 10, power);
    current = x;
    while (true) {
        //std.debug.print("rank {d} | current.val {d} | sum {d}\n", .{ rank, current.val, sum });
        sum += rank * current.val;
        rank = @divTrunc(rank, 10);
        if (rank < 1) break;
        //if (current.next == null) break;
        current = current.next.?;
    }
    return .{ len, sum };
}

fn sumThenCarryRemainders_List(arena: *std.heap.ArenaAllocator, x: TInput_List) !TOutput_List {
    const alloc = arena.allocator();
    // count len
    const l1_result: [2]i32 = sumList(x.l1);
    const l1_len = l1_result[0];
    const l2_result = sumList(x.l2);
    const l2_len = l2_result[0];
    var sum = l1_result[1] + l2_result[1];
    //std.debug.print("l1_sum is {d}\n", .{l1_result[1]});
    //std.debug.print("l2_sum is {d}\n", .{l2_result[1]});
    //std.debug.print("sum is {d}\n", .{sum});
    // solve
    var head = try alloc.create(ListNode);
    head.* = ListNode{ .val = 0, .next = null };
    var list = head;
    const max_len = if (l1_len > l2_len) l1_len else l2_len;
    // summing could make the number 1 rank higher
    // (999 + 999 = 1998), (999 + 1 = 1000)
    var power = max_len;
    var rank = std.math.pow(i32, 10, power);
    var digit = @divTrunc(sum, rank);
    var remainder = @rem(sum, rank);
    if (digit != 0) {
        list = try appendList(alloc, list, digit);
    }
    sum = remainder;
    while (true) {
        power -= 1;
        if (power < 0) break;
        rank = std.math.pow(i32, 10, power);
        digit = @divTrunc(sum, rank);
        remainder = @rem(sum, rank);
        //std.debug.print("{d} {d} {d}\n", .{ rank, digit, remainder });
        list = try appendList(alloc, list, digit);
        sum = remainder;
    }
    // this linked list implementation always has 0 in the beginning
    // (it's currently reversed relative to the target output)
    head = head.next.?;
    // the list could be 1-element one
    if (head.next == null) return head;
    // reverse by iteratively repointing after saving the pointer to the next node
    var prev: ?*ListNode = null;
    var curr: ?*ListNode = head;
    var next: ?*ListNode = undefined;
    while (curr != null) {
        next = curr.?.next;
        curr.?.next = prev;
        prev = curr;
        curr = next;
    }
    head = prev.?;
    // the power of 10 could be overshooting
    while (head.val == 0) {
        if (head.next == null) return head;
        head = head.next.?;
    }
    return head;
}

test "2 add two number lists" {
    var test_suite = TestSuite(TInput_List, TOutput_List, equalList, "add lists").init();
    defer test_suite.deinit();

    const alloc = test_suite.arena.allocator();

    try test_suite.inputs.append(.{
        .l1 = try initList(alloc, &.{ 2, 4, 3 }),
        .l2 = try initList(alloc, &.{ 5, 6, 4 }),
    });
    try test_suite.outputs.append(try initList(alloc, &.{ 7, 0, 8 }));

    try test_suite.inputs.append(.{
        .l1 = try initList(alloc, &.{0}),
        .l2 = try initList(alloc, &.{0}),
    });
    try test_suite.outputs.append(try initList(alloc, &.{0}));

    try test_suite.inputs.append(.{
        .l1 = try initList(alloc, &.{ 9, 9, 9, 9, 9, 9, 9 }),
        .l2 = try initList(alloc, &.{ 9, 9, 9, 9 }),
    });
    try test_suite.outputs.append(try initList(alloc, &.{ 8, 9, 9, 9, 0, 0, 0, 1 }));

    try test_suite.solutions.appendSlice(&.{
        .{ .run = &sumThenCarryRemainders_List },
        // this order is important
        .{ .run = &equalizeInputLengths_List }, // it adds zeros into the third case ... bruh
        // what do I need to do? clone the whole LinkedList each time? whatever
    });

    try test_suite.run();

    try std.testing.expect(!test_suite.result.failed);
}
